#ifndef _AGENT_H_
#define _AGENT_H_
#include "Glob.h"
#include "Router.h"

extern std::mt19937            rng;
extern std::shared_ptr<Router> router;

enum Model {SHORTESTPATH=9366416273040049814U,FOLLOWTHECROWD=10676684734677566718U,RANDOMWALKWAY=5792789823329120861U,WORKINGDAY};

class Agent {
private:
    uint32_t _id;
    double   _min_speed;
    double   _max_speed;

    Point2D						_position;
    Vector2D					_direction;

    std::list<Point2D>     _path;

	 Model                  _model;

public:
    Agent(void);
    Agent(const Agent&);
    Agent(const uint32_t&,const Point2D&,const std::list<Point2D>&,const double&,const double&,const Model&);
    ~Agent(void);
    Agent& operator=(const Agent&);

    Point2D  position(void) const;
    Vector2D direction(void) const;

    void geographic(const GeoCoords&);

    uint32_t id(void) const;
    Model model(void) const;

    std::list<Point2D> path(void) const;
    void path(const std::list<Point2D>&);

    void move(void);
    void random_walkway(void);
};
#endif
