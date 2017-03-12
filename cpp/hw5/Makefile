CXX=g++-6 -g --std=c++1z -fconcepts

exe=graph_test
all: ${exe}

mytype.o: mytype.h
test : mytype.o

graph.o : graph.h graph_defaults.h graph_representation.h

graph_test : graph.o

clean:
	rm -f ${exe} *.out *.o

.PHONY: all clean
