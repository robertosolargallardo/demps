#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include <glob.hh>
#include <agent.hh>

class Environment
{
public:
    typedef KDTree::KDTree<2,Agent> kdtree;

private:
    std::shared_ptr<kdtree> _tree;

public:
    Environment(void);
    Environment(const Environment&);
    Environment(const std::vector<Agent>&);
    ~Environment(void);
    Environment& operator=(const Environment&);

    Agent::Neighbors neighbors_of(const Agent&,const double&,const model_t&);
    void update(const std::vector<Agent>&);
};
#endif
