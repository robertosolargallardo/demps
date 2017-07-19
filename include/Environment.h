#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include <spatial/idle_point_multiset.hpp>
#include <spatial/neighbor_iterator.hpp>
#include "Agent.h"

class Environment {
private:
    struct Accessor {
        double operator()(spatial::dimension_type dim,const std::shared_ptr<Agent> &_agent) const {
            return(_agent->position()[dim]);
        }
    };

public:
    typedef spatial::idle_point_multiset<2,std::shared_ptr<Agent>,spatial::accessor_less<Accessor,std::shared_ptr<Agent>>> kdtree;
    typedef std::pair<double,std::shared_ptr<Agent>> neighbor;
    typedef std::vector<neighbor> neighbors;

private:
    std::array<std::shared_ptr<kdtree>,2> _container;

public:
    Environment(void);
    Environment(const Environment&);
    ~Environment(void);

    Environment& operator=(const Environment&);

    kdtree& agents(void) const;
    void insert(const std::shared_ptr<Agent>&);
    neighbors neighbors_of(const std::shared_ptr<Agent>&,const double&);
    void swap(void);
};
#endif
