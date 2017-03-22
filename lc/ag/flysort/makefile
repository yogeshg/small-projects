default: server client

# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -std=c++0x	for struct initialising
CFLAGS  = -Wall -std=c++11

server: main.cpp util.o
	$(CC) $(CFLAGS) -o server main.cpp util.o

client: client.cpp util.o
	$(CC) $(CFLAGS) -o client client.cpp util.o

testQueue:	testQueue.cpp util.o
	$(CC) $(CFLAGS) -o testQueue testQueue.cpp util.o

clean:
	$(RM) server client testQueue *.o
