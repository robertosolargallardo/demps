#include "../include/Zone.h"
Zone::Zone(void) {
    ;
}
Zone::Zone(const json &_fpolygon) {
    if(_fpolygon["geometry"]["type"]!="Polygon") {
        std::cerr << "Error::input feature is not a polygon" << std::endl;
        exit(EXIT_FAILURE);
    }
    for(auto& fpoint : _fpolygon["geometry"]["coordinates"][0]){
        double x,y,z,h;
        projector.Forward(fpoint[1],fpoint[0],h,x,y,z);
        this->_polygon.push_back(Point2D(x,y));
	 }
    this->_cdt.insert_constraint(this->_polygon.vertices_begin(),this->_polygon.vertices_end(),true);
}
Zone::Zone(const Zone &_z) {
    this->_cdt=_z._cdt;
    this->_polygon=_z._polygon;
}
Zone::~Zone(void) {
    ;
}
Zone& Zone::operator=(const Zone &_z) {
    this->_cdt=_z._cdt;
    this->_polygon=_z._polygon;
    return(*this);
}
Point2D Zone::generate(void) {
    std::vector<Point2D> points;
    CGAL::Random_points_in_triangle_mesh_2<Point2D,CDT> generator(this->_cdt);
	 CGAL::cpp11::copy_n(generator,1,std::back_inserter(points));
    std::random_shuffle(points.begin(),points.end());

    return(points[0]);
}
