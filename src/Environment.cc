#include "../include/Environment.h"

Environment::Environment(void) {
}
Environment::Environment(const Environment &_env) {
    /*this->_agents[0]=std::make_shared<std::vector<Agent>>(*_env._agents[0].get());
    this->_agents[1]->clear();
    this->_tree=_env._tree;*/
}
Environment::~Environment(void) {
    /*this->_agents[0]->clear();
    this->_agents[1]->clear();
    this->_tree->clear();*/
}

Environment& Environment::operator=(const Environment &_env) {
    //this->_agents=_env._agents;
    //this->_tree=_env._tree;
    return(*this);
}

void Environment::insert(const std::shared_ptr<Agent> &_agent) {
	this->_agents[1]->push_back(Wrapper(_agent));
}
Environment::neighbors Environment::neighbors_of(const std::shared_ptr<Agent> &_agent,const double &_max_distance) {
    double dist=0.0;
    Environment::neighbors neighbors;

    Wrapper target(_agent);
	 std::deque<Wrapper> results;
    this->_tree->find_within_range(target,_max_distance,std::back_inserter(results));
    
    for (std::deque<Wrapper>::iterator i=results.begin();i!=results.end();++i){
		  dist=target.distance(*i);
        if(dist<=_max_distance) 
           neighbors.push_back({dist,i->agent()});
    }
    return(neighbors);
}
void Environment::swap(void) {
    this->_tree->clear();
    std::swap(this->_agents[0],this->_agents[1]);
	 this->_tree->efficient_replace_and_optimise(*this->_agents[0].get());
	 this->_agents[1]->clear();
}
std::vector<std::shared_ptr<Agent>> Environment::agents(void) const {
	 std::vector<std::shared_ptr<Agent>> agents;
    std::for_each(this->_agents[0]->begin(),this->_agents[0]->end(),[&agents](const Wrapper &_wrapper)->void{agents.push_back(_wrapper.agent());});
    return(agents);
}
