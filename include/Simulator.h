#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <json.hpp>
#include <spatial/point_multiset.hpp>
#include <spatial/neighbor_iterator.hpp>
#include <GeographicLib/GeoCoords.hpp>
#include <osrm/osrm.hpp>
#include <parallel/algorithm>

#include "Zone.h"
#include "Agent.h"
#include "Router.h"
#include "Environment.h"

using namespace GeographicLib;
using json=nlohmann::json;

class Simulator {
private:

    static const std::hash<std::string> _hash;

    std::shared_ptr<Router> 		_router;
    json									_fsettings;

    Environment	_environment;

    std::vector<GeoCoords> 						_reference_points;
    std::vector<Zone> 							_initial_zones;
    std::vector<Zone> 							_reference_zones;
    //std::vector<std::shared_ptr<Agent>>  	_agents;

    void calibrate(void);
    void run(const uint32_t&,const bool&);
    void save(const uint32_t&);

public:
    Simulator(void);
    Simulator(const json&,const json&,const json&,const std::string&);

    void run(void);

    ~Simulator(void);
};
#endif
