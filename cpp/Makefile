CXX=g++-6
CXXFLAGS=-std=c++11 -O2

exe = hw3_vector_int hw3_list_int hw3_vector_big7 hw3_list_big7 hw3_vector_big15 hw3_list_big15
all: ${exe}
${exe}: hw3.cpp
hw3_vector_int: CXXFLAGS+=-D'CONTAINER=std::vector<int>'
hw3_list_int: CXXFLAGS+=-D'CONTAINER=std::list<int>'
hw3_vector_big7: CXXFLAGS+=-D'CONTAINER=std::vector<Big<7>>'
hw3_list_big7: CXXFLAGS+=-D'CONTAINER=std::list<Big<7>>'
hw3_vector_big15: CXXFLAGS+=-D'CONTAINER=std::vector<Big<15>>'
hw3_list_big15: CXXFLAGS+=-D'CONTAINER=std::list<Big<15>>'

clean:
	rm -f ${exe} *.out *.o

.PHONY: all clean
