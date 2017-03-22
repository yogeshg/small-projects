//
//  util.cpp
//  hw
//
//  Created by Yogesh Garg on 03/10/15.
//  Copyright (c) 2015 YogeshGarg. All rights reserved.
//
#include <iostream>
#include "util.h"

int MyQueue::inc(int x){
    return (CAP+x+1)%CAP;
}

MyQueue::MyQueue(){
}

MyQueue::MyQueue(int cap){
    initMyQueue(cap);
}

void MyQueue::initMyQueue(int cap){
    CAP=cap;
    _q=new long long int[CAP];
    i=(CAP+0) % CAP;
    j=(CAP-1) % CAP;
}


MyQueue::~MyQueue(){
    delete[] _q;
    }

//MyQueue::MyQueue(MyQueue const& copy){
//    CAP=copy.CAP;
//    i=copy.i;
//    j=copy.j;
//    
//    _q = new long long int[copy.CAP];
//    std::copy(&(copy._q[0]), &(copy._q[copy.CAP]), _q);
//}

void MyQueue::enqueue(long long int v){
    if(size()<CAP-1){
        j=inc(j);
        _q[j]=v;
    } else {
        std::cerr<<"Queue Capacity Reached, Ignoring "<<v<<std::endl;
    }
}

long long int MyQueue::dequeue(){
    long long int r=-1;           // Default Return
    if(size()>0){
        r=_q[i];
        i=inc(i);
    } else {
        std::cerr<<"Queue Empty, Ignoring dequeue"<<std::endl;
    }
    return r;
}

long long int MyQueue::first(){
    long long int r=-1;           // Default Return
    if(size()>0){
        r=_q[i];
    }
    return r;
}
void MyQueue::print(){
    std::cout<<"Cap:"<<CAP<<" Size:"<<size()<<" (i,j):"<<i<<j<<std::endl;
    for(int k=0;k<size();++k){
        std::cout<<_q[(i+k)%CAP]<<"<";
    }
    std::cout<<std::endl;
}

// @param n - integer to be written in the byte array
// @param b - pointer to the byte array
// @param sz - number of bytes to be written
void int2bytes(unsigned long long int n,unsigned char* b,int sz){
    for(int i=0;i<sz;++i){
        b[i]=(unsigned char) (n>>i*8);
    }
}

// @param b - pointer to the byte array
// @param sz - number of bytes to be parsed
unsigned long long int bytes2int(unsigned char* b,int sz){
    unsigned long long int r=0;
    for(int i=0;i<sz;++i)
        r+=(((unsigned long long int)b[i])<<(i*8));
    return r;
}

void printBytes(unsigned char* b,int sz){
    for(int i=0;i<sz;++i)
        std::cout<<0+b[i]<<".";
    std::cout<<std::endl;
}