#include "../include/Agent.h"

Agent::Agent(void) {
    ;
}
Agent::Agent(const Agent &_agent) {
    this->_id=_agent._id;
    this->_min_speed=_agent._min_speed;
    this->_max_speed=_agent._max_speed;
    this->_position=_agent._position;
    this->_path=_agent._path;
    this->_direction=CGAL::NULL_VECTOR;
}
Agent::Agent(const uint32_t &_id,const Point2D &_position,const double &_min_speed,const double &_max_speed) {
    this->_id=_id;
    this->_min_speed=_min_speed;
    this->_max_speed=_max_speed;
    this->_position=_position;
    this->_direction=CGAL::NULL_VECTOR;
}
Agent& Agent::operator=(const Agent &_agent) {
    this->_id=_agent._id;
    this->_min_speed=_agent._min_speed;
    this->_max_speed=_agent._max_speed;
    this->_position=_agent._position;
    this->_direction=_agent._direction;
    this->_path=_agent._path;
    return(*this);
}
uint32_t Agent::id(void) const {
    return(this->_id);
}
Agent::~Agent(void) {
}
std::list<Point2D> Agent::path(void) const {
    return(this->_path);
}
void Agent::path(const std::list<Point2D> &_path) {
    this->_path=_path;
}
void Agent::follow_path(void) {
    if(this->_path.empty()) return;

    std::uniform_real_distribution<double> speed(this->_min_speed,this->_max_speed);

    while(!this->_path.empty()){
		Point2D dst=this->_path.front();
	   double dist=sqrt(CGAL::squared_distance(this->_position,dst));

		if(dist<CLOSE_ENOUGH){
			this->_path.pop_front();
			continue;
		}

		Transformation scale(CGAL::SCALING,1,dist);
		Vector2D direction(this->_position,dst);
		direction=scale(direction);

		Transformation translate(CGAL::TRANSLATION,direction*speed(rng));
		
	   //std::cout << this->_position << std::endl;
		this->_position=translate(this->_position);
	   //std::cout << this->_position << std::endl;
		//exit(0);
		break;
	 }
}
Vector2D Agent::direction(void) const {
    return(this->_direction);
}
Point2D Agent::position(void) const {
    return(this->_position);
}
