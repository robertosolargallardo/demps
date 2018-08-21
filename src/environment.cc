#include <environment.hh>

Environment::Environment(void)
{
    this->_tree=std::make_shared<kdtree>(/*std::ptr_fun(Environment::tac)*/);
}
Environment::Environment(const std::vector<Agent> &_agents)
{
    this->_tree=std::make_shared<kdtree>(/*std::ptr_fun(Environment::tac)*/);

    for(auto& agent : _agents)
        this->_tree->insert(/*std::make_shared<Agent>(agent)*/agent);

    this->_tree->optimise();
}
Environment::Environment(const Environment &_env)
{
    this->_tree=std::make_shared<kdtree>(*_env._tree);
}
Environment::~Environment(void)
{
    this->_tree->clear();
}

Environment& Environment::operator=(const Environment &_env)
{
    this->_tree=std::make_shared<kdtree>(*_env._tree);
    return(*this);
}

Agent::Neighbors Environment::neighbors_of(const Agent &_agent,const double &_max_distance,const model_t &_model)
{
    Agent::Neighbors neighbors;
    std::deque</*std::shared_ptr<Agent>*/Agent> results;
    double dist=0.0;

    this->_tree->find_within_range(/*std::make_shared<Agent>(_agent)*/_agent,_max_distance,std::back_inserter(results));

    //for (std::deque<std::shared_ptr<Agent>>::iterator it=results.begin(); it!=results.end(); ++it) {
    for (std::deque<Agent>::iterator agent=results.begin(); agent!=results.end(); ++agent)
        {
            //std::shared_ptr<Agent> agent=*it;
            if(agent->model()==_model)
                {
                    dist=_agent.distance(*agent);
                    if(dist<=_max_distance)
                        neighbors.push_back(/*Agent(*agent)*/*agent);
                }
        }

    return(neighbors);
}
void Environment::update(std::vector<Agent> &_agents) const
{
    /*for(auto& agent: (*this->_tree))
    	agent->update(_agents[agent->id()].position(),_agents[agent->id()].direction());*/

    this->_tree->clear();

    for(auto& agent : _agents)
        this->_tree->insert(/*std::make_shared<Agent>(agent)*/agent);

    this->_tree->optimise();
}
