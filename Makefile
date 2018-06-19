CXX=g++
LIBRARY=-L/usr/local/lib
INCLUDE=-I/usr/local/include/nlohmann -I/usr/local/include/osrm
CXXFLAGS=-std=c++14 -g -ggdb -Wall -losrm -lGeographic -O3 -ltbb -lboost_system -lboost_filesystem -lpthread -lboost_iostreams -lboost_thread -lrt -fopenmp -lCGAL

OBJS=obj/sim.o obj/Zone.o obj/Simulator.o obj/Agent.o obj/Router.o obj/Environment.o
TARGET=demps

$(TARGET):$(OBJS)
	       $(CXX) $^ -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)

obj/sim.o:src/sim.cc
	       $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)
obj/Zone.o:src/Zone.cc include/Zone.h
	        $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)
obj/Simulator.o:src/Simulator.cc include/Simulator.h
	             $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)
obj/Agent.o:src/Agent.cc include/Agent.h
	         $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)
obj/Router.o:src/Router.cc include/Router.h
	         $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)
obj/Environment.o:src/Environment.cc include/Environment.h
	         $(CXX) -c $< -o $@ $(CXXFLAGS) $(LIBRARY) $(INCLUDE)

clean:
		${RM} $(OBJS) $(TARGET)
