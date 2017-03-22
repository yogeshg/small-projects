# g++ main.cpp -std=c++0x -o circularprinter.out

# the compiler: gcc for C program, define as g++ for C++
CC = g++-4.8

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -std=c++0x	for struct initialising
CFLAGS  = -std=c++0x

# the build target executable:
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
