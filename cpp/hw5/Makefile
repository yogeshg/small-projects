CXX=g++-6 --std=c++1z -fconcepts

exe=graph_test
all: ${exe}

graph.o : graph.h

graph_test : graph.o

clean:
	rm -f ${exe} *.out *.o

.PHONY: all clean
