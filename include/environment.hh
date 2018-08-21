#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include <glob.hh>
#include <agent.hh>

class Environment
{
public:
    /*inline static double tac(std::shared_ptr<Agent> agent,size_t k) {return((agent->position())[k]);}
    typedef KDTree::KDTree<2,std::shared_ptr<Agent>,std::pointer_to_binary_function<std::shared_ptr<Agent>,size_t,double>> kdtree;*/
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
    void update(std::vector<Agent>&) const;
};
#endif
