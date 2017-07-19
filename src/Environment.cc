#include "../include/Environment.h"

Environment::Environment(void) {
    this->_container[0]=std::make_shared<Environment::kdtree>();
    this->_container[1]=std::make_shared<Environment::kdtree>();
}
Environment::Environment(const Environment &_env) {
    this->_container[0]=std::make_shared<Environment::kdtree>(*_env._container[0].get());
    this->_container[1]=std::make_shared<Environment::kdtree>(*_env._container[1].get());
}
Environment::~Environment(void) {
    this->_container[0]->clear();
    this->_container[1]->clear();
}

Environment& Environment::operator=(const Environment &_env) {
    this->_container[0]=std::make_shared<Environment::kdtree>(*_env._container[0].get());
    this->_container[1]=std::make_shared<Environment::kdtree>(*_env._container[1].get());
    return(*this);
}

void Environment::insert(const std::shared_ptr<Agent> &_agent) {
    this->_container[1]->insert(_agent);
}
Environment::neighbors Environment::neighbors_of(const std::shared_ptr<Agent> &_agent,const double &_max_distance) {
    double dist=0.0;
    std::vector<std::pair<double,std::shared_ptr<Agent>>> neighbors;

    this->_container[0]->rebalance();

    for(spatial::neighbor_iterator<Environment::kdtree> iter=spatial::neighbor_begin((*this->_container[0].get()),_agent); iter!=spatial::neighbor_end((*this->_container[0].get()),_agent); ++iter) {
        dist=spatial::distance(iter);

        if(dist>_max_distance) break;
        neighbors.push_back(std::make_pair(dist,*iter));
    }
    return(neighbors);
}
void Environment::swap(void) {
    std::swap(this->_container[0],this->_container[1]);
    this->_container[0]->rebalance();
    this->_container[1]->clear();
}
Environment::kdtree& Environment::agents(void) const {
    return(*this->_container[0]);
}
