//
//  util.h
//  hw
//
//  Created by Yogesh Garg on 03/10/15.
//  Copyright (c) 2015 YogeshGarg. All rights reserved.
//

#ifndef __hw__util__
#define __hw__util__

#include <stdio.h>

class MyQueue {
private:
    int CAP;    // Capacity of the queue
    int i,j;    // Start and End Indices. End Index should aways be kept "empty"
    long long int* _q;
    int inc(int x);
public:
    MyQueue();
    MyQueue(int cap);
    void initMyQueue(int cap);
    ~MyQueue();
//    MyQueue(MyQueue const& copy);
    int size(){ return (CAP+j+1-i)%CAP; }   // Max size is CAP-1
    void enqueue(long long int v);
    long long int dequeue();
    long long int first();
    void print();
};

void int2bytes(unsigned long long int n,unsigned char* b,int sz);
unsigned long long int bytes2int(unsigned char* b,int sz);
void printBytes(unsigned char* b,int sz);

#endif /* defined(__hw__util__) */
