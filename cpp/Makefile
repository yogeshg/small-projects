CXX=g++-6
CXXFLAGS=-std=c++11 -O2

exe = hw3_vector_int hw3_list_int hw3_vector_big7 hw3_list_big7 hw3_vector_big15 hw3_list_big15 hw3_set_int hw3_set_big7 hw3_set_big15 hw3_setopt_int hw3_setopt_big7 hw3_setopt_big15
all: ${exe}
${exe}: hw3.cpp
hw3_vector_int: CXXFLAGS+=-D'CONTAINER=std::vector<int>'
hw3_list_int: CXXFLAGS+=-D'CONTAINER=std::list<int>'
hw3_vector_big7: CXXFLAGS+=-D'CONTAINER=std::vector<Big<7>>'
hw3_list_big7: CXXFLAGS+=-D'CONTAINER=std::list<Big<7>>'
hw3_vector_big15: CXXFLAGS+=-D'CONTAINER=std::vector<Big<15>>'
hw3_list_big15: CXXFLAGS+=-D'CONTAINER=std::list<Big<15>>'
hw3_set_int: CXXFLAGS+=-D'CONTAINER=std::set<int>'
# hw3_set_big7: CXXFLAGS+=-D'CONTAINER=std::set<Big<7>>'
# hw3_set_big15: CXXFLAGS+=-D'CONTAINER=std::set<Big<15>'
hw3_setopt_int: CXXFLAGS+=-D'CONTAINER=std::set<int>' -DCONTAINER_INSERTS
# hw3_setopt_big7: CXXFLAGS+=-D'CONTAINER=std::set<Big<7>>' -DCONTAINER_INSERTS
# hw3_setopt_big15: CXXFLAGS+=-D'CONTAINER=std::set<Big<15>' -DCONTAINER_INSERTS

touch:
	touch hw3_vector_int.cpp
	touch hw3_list_int.cpp
	touch hw3_vector_big7.cpp
	touch hw3_list_big7.cpp
	touch hw3_vector_big15.cpp
	touch hw3_list_big15.cpp
	touch hw3_set_int.cpp
	touch hw3_setopt_int.cpp

clean:
	rm -f ${exe} *.out *.o

.PHONY: all clean touch
