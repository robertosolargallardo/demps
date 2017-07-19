#include <iostream>
#include <fstream>
#include <unistd.h>
#include <json.hpp>
#include "../include/Glob.h"
#include "../include/Simulator.h"

std::random_device device;
std::mt19937 rng(0/*device()*/);

LocalCartesian projector;

int main(int argc,char** argv) {
    char c;
    std::string map_osrm;
    json settings;
    json initial_zones;
    json reference_zones;
    json reference_point;

    while((c=getopt(argc,argv,"m:s:i:r:p:"))!=-1) {
        switch(c) {
        case 'm': {
            map_osrm=std::string(optarg);
            break;
        }
        case 's': {
            std::ifstream ifs;
            ifs.open(optarg,std::ifstream::in);
            ifs >> settings;
            ifs.close();
            break;
        }
        case 'i': {
            std::ifstream ifs;
            ifs.open(optarg,std::ifstream::in);
            ifs >> initial_zones;
            ifs.close();
            break;
        }
        case 'r': {
            std::ifstream ifs;
            ifs.open(optarg,std::ifstream::in);
            ifs >> reference_zones;
            ifs.close();
            break;
        }
        case 'p': {
            std::ifstream ifs;
            ifs.open(optarg,std::ifstream::in);
            ifs >> reference_point;
            ifs.close();
            break;
        }
        default: {
            exit(EXIT_FAILURE);
            break;
        }
        }
    }
    if(map_osrm.empty()) {
        std::cerr << "Mandatory parameter -m <map.osrm> needed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(settings.empty()) {
        std::cerr << "Mandatory parameter -s <settings.json> needed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(initial_zones.empty()) {
        std::cerr << "Mandatory parameter -i <initial-zones.json> needed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(reference_zones.empty()) {
        std::cerr << "Mandatory parameter -r <reference-zones.json> needed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(reference_point.empty()) {
        std::cerr << "Mandatory parameter -p <reference-point.json> needed" << std::endl;
        exit(EXIT_FAILURE);
    } else
		  projector=LocalCartesian(reference_point["features"][0]["geometry"]["coordinates"][1],reference_point["features"][0]["geometry"]["coordinates"][0],0,Geocentric::WGS84());

    Simulator sim(settings,initial_zones,reference_zones,map_osrm);

    sim.run();

    return(0);
}
