#include "../include/Simulator.h"

Simulator::Simulator(void) {

}
Simulator::Simulator(const json &_fsettings,const json &_finitial_zones,const json &_freference_zones,const std::string &_map_osrm) {
    this->_router=std::make_shared<Router>(_map_osrm);
    this->_fsettings=_fsettings;

    for(auto& feature : _freference_zones["features"])
        this->_reference_zones.push_back(Zone(feature));

    for(auto& feature : _finitial_zones["features"])
        this->_initial_zones.push_back(Zone(feature));

    uint32_t id=0U;
    std::uniform_int_distribution<uint32_t> zone(0U,this->_initial_zones.size()-1U);
    for(auto& fagent : _fsettings["agents"]) {
        for(uint32_t i=0U; i<uint32_t(fagent["number"]); i++,id++) {
            auto agent=std::make_shared<Agent>(id,this->_initial_zones[zone(rng)].generate(),fagent["speed"]["min"],fagent["speed"]["max"]);

            switch(this->_hash(fagent["model"])) {
            case SHORTESTPATH: {
                double distance=DBL_MAX;
                for(auto &reference_zone : this->_reference_zones) {
                    auto response=this->_router->route(agent->position(),reference_zone.generate());
                    if(response.distance()<distance) {
                        distance=response.distance();
                        agent->path(response.path());
                    }
                }
                break;
            }
            case FOLLOWTHECROWD: {
                break;
            }
            default: {
                std::cerr << "error::simulator_constructor::unknown_mobility_model::\"" << fagent["model"] << "\"" << std::endl;
                exit(EXIT_FAILURE);
            }
            }
            this->_environment.insert(agent);
        }
    }
    this->_environment.swap();
}
void Simulator::calibrate(void) {

}
void Simulator::run(void) {
    this->run(this->_fsettings["duration"],true);
}
void Simulator::save(const uint32_t &_t) {
    std::ofstream ofs(this->_fsettings["output"]["directory-path"].get<std::string>()+"/"+this->_fsettings["output"]["filename-prefix"].get<std::string>()+std::to_string(_t)+this->_fsettings["output"]["filename-sufix"].get<std::string>());
    for(auto& agent : this->_environment.agents()){
        double latitude,longitude,h;
        projector.Reverse(agent->position()[0],agent->position()[1],0,latitude,longitude,h);
        ofs << agent->id() << " " << latitude << " " << longitude << std::endl;
    }
}
void Simulator::run(const uint32_t &_duration,const bool &_save_to_disk) {
    std::cout << "simulating" << std::endl;

    for(uint32_t t=0U; t<_duration; t++) {
        if(_save_to_disk) this->save(t);

        for(auto& agent : this->_environment.agents()) {
            Environment::neighbors neighbors;//=this->_environment.neighbors_of(agent,0.0);

            auto copy=std::make_shared<Agent>(*agent.get());
            copy->follow_path();
            this->_environment.insert(copy);
        }

        /*auto& environment=this->_environment;
        auto& agents=this->_environment.agents();
        __gnu_parallel::for_each(agents.begin(),agents.end(),[&environment](const std::shared_ptr<Agent> &_agent)->void {
        	auto copy=std::make_shared<Agent>(*_agent.get());
        	Environment::neighbors neighbors=environment.neighbors_of(copy,10.0);
        	copy->move();
        	#pragma omp critical
        		environment.insert(copy);
        });*/
        this->_environment.swap();
    }
}

Simulator::~Simulator(void) {
    this->_initial_zones.clear();
    this->_reference_zones.clear();
}
