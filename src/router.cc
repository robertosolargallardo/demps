#include <router.hh>
Router::Router(void) {
    ;
}
Router::Router(const Router &_router) {
    this->_config=_router._config;
    this->_projector=_router._projector;
    this->_osrm=std::make_shared<osrm::OSRM>(this->_config);
}
Router::Router(const json &_freference_point,const std::string &_map_osrm) {
    this->_config.storage_config={_map_osrm};
    this->_config.use_shared_memory=false;
    this->_osrm=std::make_shared<osrm::OSRM>(this->_config);

    this->_projector=LocalCartesian(_freference_point["features"][0]["geometry"]["coordinates"][1],_freference_point["features"][0]["geometry"]["coordinates"][0],0,Geocentric::WGS84());
}
Router::~Router(void) {
    ;
}
Router& Router::operator=(const Router &_router) {
    this->_config=_router._config;
    this->_projector=_router._projector;
    this->_osrm=std::make_shared<osrm::OSRM>(this->_config);
    return(*this);
}
Router::Response Router::route(const Point2D &_src,const Point2D &_dst) {
    osrm::RouteParameters params;
    params.steps=true;
    double src_latitude,src_longitude,src_h;
    double dst_latitude,dst_longitude,dst_h;

    this->_projector.Reverse(_src[0],_src[1],0,src_latitude,src_longitude,src_h);
    this->_projector.Reverse(_dst[0],_dst[1],0,dst_latitude,dst_longitude,dst_h);

    params.coordinates.push_back({osrm::util::FloatLongitude{src_longitude},osrm::util::FloatLatitude{src_latitude}});
    params.coordinates.push_back({osrm::util::FloatLongitude{dst_longitude},osrm::util::FloatLatitude{dst_latitude}});

    osrm::json::Object result;
    const auto status=this->_osrm->Route(params,result);

    Response response;
    std::list<Point2D> path;

    if(status==osrm::Status::Ok) {
        auto &routes=result.values["routes"].get<osrm::json::Array>();
        auto &route=routes.values.begin()->get<osrm::json::Object>();

        auto &legs=route.values["legs"].get<osrm::json::Array>();
        auto &leg=legs.values.begin()->get<osrm::json::Object>();
        auto &steps=leg.values["steps"].get<osrm::json::Array>();

        for(auto &step : steps.values) {
            auto &intersections=step.get<osrm::json::Object>().values["intersections"].get<osrm::json::Array>();
            for(auto &intersection : intersections.values) {
                auto &location=intersection.get<osrm::json::Object>().values["location"].get<osrm::json::Array>();
                double x,y,z,h;
                this->_projector.Forward(location.values.at(1).get<osrm::json::Number>().value,location.values.at(0).get<osrm::json::Number>().value,h,x,y,z);
                path.push_back(Point2D(x,y));
            }
        }
        response=Response(route.values["distance"].get<osrm::json::Number>().value,route.values["duration"].get<osrm::json::Number>().value,path);
    }
    return(response);
}
Router::Response Router::route(const Point2D &_src,const double &_radius) {
    static thread_local std::random_device device;
    static thread_local std::mt19937 rng(device());

    Response response;

    std::uniform_real_distribution<double> radius(0.0,_radius);
    std::uniform_real_distribution<double> angle(0.0,2.0*M_PI);

    do {
        double r=radius(rng);
        double a=angle(rng);
        Point2D dst(_src[0]+(r*cos(a)),_src[1]+(r*sin(a)));
        response=this->route(_src,dst);
    } while(response.path().empty());

    return(response);
}
