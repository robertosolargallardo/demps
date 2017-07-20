#ifndef _NEIGHBOR_H_
#define _NEIGHBOR_H_
#include "Glob.h"

struct Neighbor {
    double   distance;
    uint32_t id;
    Point2D 	position;
    Vector2D direction;
};
typedef std::vector<Neighbor> Neighbors;

#endif
