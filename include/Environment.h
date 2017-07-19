#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include "Glob.h"
#include "Agent.h"

class Environment {
private:
    class Wrapper {
    public:
        typedef double value_type;
        std::shared_ptr<Agent> _agent;

        Wrapper(void) {
            ;
        }
        Wrapper(const std::shared_ptr<Agent> &_agent) {
            this->_agent=_agent;
        }
        Wrapper(const Wrapper &_wrapper) {
            this->_agent=_wrapper._agent;
        }
        Wrapper& operator=(const Wrapper &_wrapper) {
            this->_agent=_wrapper._agent;
            return(*this);
        }
        ~Wrapper(void) {
            ;
        }
        inline value_type operator[](size_t const k) const {
            return(this->_agent->position()[k]);
        }
        std::shared_ptr<Agent> agent(void) const {
            return(this->_agent);
        }
		  double distance(Wrapper const &_wrapper) const{
            return(sqrt(CGAL::squared_distance(this->_agent->position(),_wrapper.agent()->position())));
        }
    };


public:
    typedef KDTree::KDTree<2,Wrapper> kdtree;
    struct Neighbor{
		double                 distance;
      std::shared_ptr<Agent> agent;
	 };
    typedef std::vector<Neighbor> neighbors;
   

private:
    std::array<std::shared_ptr<std::vector<Wrapper>>,2>  _agents;
    std::shared_ptr<kdtree> 					               _tree;

public:
    Environment(void);
    Environment(const Environment&);
    ~Environment(void);

    Environment& operator=(const Environment&);

    std::vector<std::shared_ptr<Agent>> agents(void) const;
    void insert(const std::shared_ptr<Agent>&);
    neighbors neighbors_of(const std::shared_ptr<Agent>&,const double&);
    void swap(void);
};
#endif
