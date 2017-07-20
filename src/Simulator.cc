#include "../include/Simulator.h"

Simulator::Simulator(void) {

}
Simulator::Simulator(const json &_fsettings,const json &_finitial_zones,const json &_freference_zones) {
    this->_fsettings=_fsettings;

    for(auto& feature : _freference_zones["features"])
        this->_reference_zones.push_back(Zone(feature));

    for(auto& feature : _finitial_zones["features"])
        this->_initial_zones.push_back(Zone(feature));

    uint32_t id=0U;
    std::uniform_int_distribution<uint32_t> zone(0U,this->_initial_zones.size()-1U);
    for(auto& fagent : _fsettings["agents"]) {
        for(uint32_t i=0U; i<uint32_t(fagent["number"]); i++,id++) {
            Point2D position=this->_initial_zones[zone(rng)].generate();
            auto response=router->route(position,RANDOM_WALKWAY_RADIUS);
            auto agent=std::make_shared<Agent>(id,position,response.path(),fagent["speed"]["min"],fagent["speed"]["max"],Model(this->_hash(fagent["model"].get<std::string>())));
            this->_agents.push_back(agent);
        }
    }
    this->_env=std::make_shared<Environment>(this->_agents);
}
void Simulator::calibrate(void) {
    std::cout << "calibrating" << std::endl;

    for(uint32_t t=0U; t<CALIBRATION_TIME; t++) {
        for(auto& agent : this->_agents)
            agent->random_walkway();
    }

    for(auto& agent : this->_agents) {
        switch(agent->model()) {
        case SHORTESTPATH: {
            double distance=DBL_MAX;
            for(auto &reference_zone : this->_reference_zones) {
                auto response=router->route(agent->position(),reference_zone.generate());
                if(response.distance()<distance) {
                    distance=response.distance();
                    agent->path(response.path());
                }
            }
            break;
        }
        case RANDOMWALKWAY: {
            break;
        }
        case FOLLOWTHECROWD: {
            break;
        }
        default: {
            std::cerr << "error::simulator_constructor::unknown_mobility_model::\"" << agent->model() << "\"" << std::endl;
            exit(EXIT_FAILURE);
        }
        }
    }
    //this->_env->update(this->_agents);
}
void Simulator::run(void) {
    this->run(this->_fsettings["duration"],true);
}
void Simulator::run(const uint32_t &_duration,const bool &_save_to_disk) {
    std::cout << "simulating" << std::endl;

    for(uint32_t t=0U; t<_duration; t++) {
        if(_save_to_disk) this->save(t);

        for(auto& agent : this->_agents) {
            switch(agent->model()) {
            case SHORTESTPATH: {
                agent->move();
                break;
            }
            case RANDOMWALKWAY: {
                agent->random_walkway();
                break;
            }
            case FOLLOWTHECROWD: {
                break;
            }
            default: {
                std::cerr << "error::simulator_constructor::unknown_mobility_model::\"" << agent->model() << "\"" << std::endl;
                exit(EXIT_FAILURE);
            }
            }
            /*Environment::neighbors neighbors;//=this->_environment.neighbors_of(agent,0.0);

            auto copy=std::make_shared<Agent>(*agent.get());
            copy->follow_path();
            this->_environment.insert(copy);*/
        }
        //this->_env->update(this->_agents);
    }
}

Simulator::~Simulator(void) {
    this->_agents.clear();
    this->_initial_zones.clear();
    this->_reference_zones.clear();
}
void Simulator::save(const uint32_t &_t) {
    std::ofstream ofs(this->_fsettings["output"]["directory-path"].get<std::string>()+"/"+this->_fsettings["output"]["filename-prefix"].get<std::string>()+std::to_string(_t)+this->_fsettings["output"]["filename-sufix"].get<std::string>());

    for(auto& agent : this->_agents) {
        double latitude,longitude,h;
        projector->Reverse(agent->position()[0],agent->position()[1],0,latitude,longitude,h);
        ofs << agent->id() << " " << latitude << " " << longitude << std::endl;
    }
}
