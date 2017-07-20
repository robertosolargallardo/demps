#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_
#include "Glob.h"
#include "Zone.h"
#include "Agent.h"
#include "Router.h"
#include "Environment.h"

extern std::shared_ptr<Router> router;

class Simulator {
private:

    static const std::hash<std::string> _hash;

    std::shared_ptr<Environment> _env;
    json									_fsettings;

    std::vector<GeoCoords> 					_reference_points;
    std::vector<Zone> 							_initial_zones;
    std::vector<Zone> 							_reference_zones;
    std::vector<std::shared_ptr<Agent>>  	_agents;

    void calibrate(void);
    void run(const uint32_t&,const bool&);
    void save(const uint32_t&);

public:
    Simulator(void);
    Simulator(const json&,const json&,const json&);

    void run(void);

    ~Simulator(void);
};
#endif
