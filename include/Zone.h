#ifndef _ZONE_H_
#define _ZONE_H_
#include "Glob.h"

extern std::mt19937   rng;
extern std::shared_ptr<LocalCartesian> projector;

class Zone {
private:
    Polygon2D            _polygon;
    CDT                  _cdt;

public:
    Zone(void);
    Zone(const json&);
    Zone(const Zone&);
    ~Zone(void);

    Zone& operator=(const Zone&);

    Point2D generate(void);
};
#endif
