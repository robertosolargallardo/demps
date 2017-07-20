#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include "Glob.h"
#include "Agent.h"
#include "Neighbor.h"

class Environment {
private:
    class Node {
    public:
        typedef double value_type;
        uint32_t  _id;
        Point2D	_position;
        Vector2D	_direction;

        Node(void) {
            ;
        }
        Node(const std::shared_ptr<Agent> &_agent) {
            this->_id=_agent->id();
            this->_position=_agent->position();
            this->_direction=_agent->direction();

        }
        Node(const Node &_node) {
            this->_id=_node._id;
            this->_position=_node._position;
            this->_direction=_node._direction;
        }
        Node& operator=(const Node &_node) {
            this->_id=_node._id;
            this->_position=_node._position;
            this->_direction=_node._direction;
            return(*this);
        }
        ~Node(void) {
            ;
        }
        inline value_type operator[](size_t const k) const {
            return(this->_position[k]);
        }
        double distance(Node const &_node) const {
            return(sqrt(CGAL::squared_distance(this->_position,_node._position)));
        }
    };


public:
    typedef KDTree::KDTree<2,Node> kdtree;

private:
    std::map<uint32_t,Node>  _nodes;
    std::shared_ptr<kdtree>  _tree;

public:
    Environment(void);
    Environment(const Environment&);
    Environment(const std::vector<std::shared_ptr<Agent>>&);
    ~Environment(void);
    Environment& operator=(const Environment&);

    Neighbors neighbors_of(const std::shared_ptr<Agent>&,const double&);
    void update(const std::vector<std::shared_ptr<Agent>>&);
};
#endif
