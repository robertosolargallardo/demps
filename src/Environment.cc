#include "../include/Environment.h"

Environment::Environment(void) {
    this->_tree=std::make_shared<kdtree>();
}
Environment::Environment(const std::vector<std::shared_ptr<Agent>> &_agents) {
    this->_tree=std::make_shared<kdtree>();

    for(auto& agent : _agents) {
        this->_nodes[agent->id()]=Node(agent);
        this->_tree->insert(this->_nodes[agent->id()]);
    }
    this->_tree->optimise();
}
Environment::Environment(const Environment &_env) {
    this->_tree=std::make_shared<kdtree>(*_env._tree);
    this->_nodes=_env._nodes;
}
Environment::~Environment(void) {
    this->_nodes.clear();
    this->_tree->clear();
}

Environment& Environment::operator=(const Environment &_env) {
    return(*this);
}

Neighbors Environment::neighbors_of(const std::shared_ptr<Agent> &_agent,const double &_max_distance) {
    double dist=0.0;
    Neighbors neighbors;

    Node query(_agent);
    std::deque<Node> results;

    this->_tree->find_within_range(query,_max_distance,std::back_inserter(results));

    for (std::deque<Node>::iterator node=results.begin(); node!=results.end(); ++node) {
        dist=query.distance(*node);
        if(dist<=_max_distance)
            neighbors.push_back({dist,node->_id,node->_model,node->_position,node->_direction});
    }

    return(neighbors);
}
void Environment::update(const std::vector<std::shared_ptr<Agent>> &_agents) {
    for(auto& agent : _agents)
        this->_nodes[agent->id()]=Node(agent);
    this->_tree->optimise();
}
