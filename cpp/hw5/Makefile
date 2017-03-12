CXX=g++-6 -g --std=c++1z -fconcepts

exe=main debug graph_test
all: ${exe}

mytype.o: mytype.h
test : mytype.o

graph.o : graph.h graph_defaults.h graph_representation.h

graph_test : graph.o

clean:
	rm -f ${exe} *.out *.o

.PHONY: all clean

main : graph_test.cpp graph.o
	g++-6 -fconcepts -O2 -std=c++1z graph_test.cpp graph.o -o main

debug : graph_test.cpp graph.o
	g++-6 -fconcepts -O0 -std=c++1z -g3 graph_test.cpp graph.o -o debug

valgrind : debug
	valgrind -v --num-callers=20 --leak-check=yes --leak-resolution=high --show-reachable=yes ./debug

