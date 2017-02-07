CXX=g++-6
CXXFLAGS=-std=c++11 -O2

exe = hw3_vector_int hw3_list_int hw3_vector_big7 hw3_list_big7 hw3_vector_big15 hw3_list_big15 hw3_set_int hw3_set_big7 hw3_set_big15 hw3_set_int_opt hw3_set_big7_opt hw3_set_big15_opt
all: ${exe}
${exe}: hw3.cpp
hw3_vector_int: CXXFLAGS+=-D'CONTAINER=std::vector<int>'
hw3_list_int: CXXFLAGS+=-D'CONTAINER=std::list<int>'
hw3_vector_big7: CXXFLAGS+=-D'CONTAINER=std::vector<Big<7>>'
hw3_list_big7: CXXFLAGS+=-D'CONTAINER=std::list<Big<7>>'
hw3_vector_big15: CXXFLAGS+=-D'CONTAINER=std::vector<Big<15>>'
hw3_list_big15: CXXFLAGS+=-D'CONTAINER=std::list<Big<15>>'
hw3_set_int: CXXFLAGS+=-D'CONTAINER=std::set<int>'
hw3_set_big7: CXXFLAGS+=-D'CONTAINER=std::set<Big<7>>'
hw3_set_big15: CXXFLAGS+=-D'CONTAINER=std::set<Big<15>'
hw3_set_int_opt: CXXFLAGS+=-D'CONTAINER=std::set<int>' -DCONTAINER_INSERTS
hw3_set_big7_opt: CXXFLAGS+=-D'CONTAINER=std::set<Big<7>>' -DCONTAINER_INSERTS
hw3_set_big15_opt: CXXFLAGS+=-D'CONTAINER=std::set<Big<15>' -DCONTAINER_INSERTS

clean:
	rm -f ${exe} *.out *.o

.PHONY: all clean
