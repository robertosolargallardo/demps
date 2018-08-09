#include <environment.hh>

Environment::Environment(void) {
    this->_tree=std::make_shared<kdtree>();
}
Environment::Environment(const std::vector<Agent> &_agents) {
    this->_tree=std::make_shared<kdtree>();

    for(auto& agent : _agents) 
        this->_tree->insert(Agent(agent));

    this->_tree->optimise();
}
Environment::Environment(const Environment &_env) {
    this->_tree=std::make_shared<kdtree>(*_env._tree);
}
Environment::~Environment(void) {
    this->_tree->clear();
}

Environment& Environment::operator=(const Environment &_env) {
    this->_tree=std::make_shared<kdtree>(*_env._tree);
    return(*this);
}

Agent::Neighbors Environment::neighbors_of(const Agent &_agent,const double &_max_distance,const model_t &_model) {
    Agent::Neighbors neighbors;
    std::deque<Agent> results;
    double dist=0.0;

    this->_tree->find_within_range(_agent,_max_distance,std::back_inserter(results));

    for (std::deque<Agent>::iterator it=results.begin(); it!=results.end(); ++it) {
        Agent agent=*it;
        if(agent.model()==_model){   
            dist=_agent.distance(agent);
            if(dist<=_max_distance)
                neighbors.push_back(agent);
        }
    }

    return(neighbors);
}
void Environment::update(const std::vector<Agent> &_agents) {
    this->_tree->clear();

    for(auto& agent : _agents) 
        this->_tree->insert(Agent(agent));

    this->_tree->optimise();
}
