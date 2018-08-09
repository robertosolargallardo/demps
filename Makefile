CXX=g++
LIBRARY=-L/usr/local/lib
INCLUDE=-I/usr/local/include/nlohmann -I/usr/local/include/osrm -I./include -I/home/rsolar/SIMILARITY_CACHING/src/liblistofclusters/include/
CXXFLAGS=-std=c++14 -g -ggdb -Wall -losrm -lGeographic -O3 -ltbb -lboost_system -lboost_filesystem -lpthread -lboost_iostreams -lboost_thread -lrt -fopenmp -lCGAL

OBJS=obj/demps.o obj/zone.o obj/simulator.o obj/agent.o obj/router.o obj/environment.o
TARGET=demps

$(TARGET):$(OBJS)
	       $(CXX) $^ -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)

obj/demps.o:src/demps.cc
	       $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)
obj/zone.o:src/zone.cc include/zone.hh
	        $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)
obj/simulator.o:src/simulator.cc include/simulator.hh
	             $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)
obj/agent.o:src/agent.cc include/agent.hh
	         $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)
obj/router.o:src/router.cc include/router.hh
	         $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)
obj/environment.o:src/environment.cc include/environment.hh
	         $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)

clean:
		${RM} $(OBJS) $(TARGET)
