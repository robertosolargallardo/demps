#ifndef _AGENT_HH_
#define _AGENT_HH_
#include <glob.hh>


class Agent
{
public:
    typedef double value_type;
    typedef std::vector<Agent> Neighbors;

private:
    uint32_t _id;
    double   _min_speed;
    double   _max_speed;

    Point2D  _position;
    Vector2D _direction;

    model_t  _model;

public:
    Agent(void);
    Agent(const Agent&);
    Agent(const uint32_t&,const Point2D&,const double&,const double&,const model_t&);
    ~Agent(void);
    Agent& operator=(const Agent&);

    Point2D  position(void) const;
    Vector2D direction(void) const;

    void geographic(const GeoCoords&);

    void position(const Point2D&);
    void direction(const Vector2D&);
    void update(const Point2D&,const Vector2D&);

    uint32_t id(void) const;
    model_t model(void) const;

    void follow_path(std::list<Point2D>&);
    void random_walkway(std::list<Point2D>&);
    void follow_the_crowd(const Neighbors&);

    double distance(const Agent&) const;
    value_type operator[](size_t k) const
    {
        return(this->_position[k]);
    }
};
#endif
