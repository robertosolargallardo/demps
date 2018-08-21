#include <zone.hh>
Zone::Zone(void)
{
    ;
}
Zone::Zone(const json &_freference_point,const json &_fpolygon)
{
    this->_projector=LocalCartesian(_freference_point["features"][0]["geometry"]["coordinates"][1],_freference_point["features"][0]["geometry"]["coordinates"][0],0,Geocentric::WGS84());

    if(_fpolygon["geometry"]["type"]!="Polygon")
        {
            std::cerr << "Error::input feature is not a polygon" << std::endl;
            exit(EXIT_FAILURE);
        }
    for(auto& fpoint : _fpolygon["geometry"]["coordinates"][0])
        {
            double x,y,z,h;
            this->_projector.Forward(fpoint[1],fpoint[0],h,x,y,z);
            this->_polygon.push_back(Point2D(x,y));
        }
    this->_cdt.insert_constraint(this->_polygon.vertices_begin(),this->_polygon.vertices_end(),true);
    CGAL::refine_Delaunay_mesh_2(this->_cdt,Mesh_2_criteria());

}
Zone::Zone(const Zone &_z)
{
    this->_cdt=_z._cdt;
    this->_polygon=_z._polygon;
    this->_projector=_z._projector;
}
Zone::~Zone(void)
{
    ;
}
Zone& Zone::operator=(const Zone &_z)
{
    this->_cdt=_z._cdt;
    this->_polygon=_z._polygon;
    this->_projector=_z._projector;
    return(*this);
}
Point2D Zone::generate(void)
{
    std::vector<Point2D> points;
    CGAL::Random_points_in_triangle_mesh_2<Point2D,CDT> generator(this->_cdt);
    CGAL::cpp11::copy_n(generator,1,std::back_inserter(points));
    std::random_shuffle(points.begin(),points.end());

    return(points[0]);
}
