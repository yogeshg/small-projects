//
//  main.cpp
//  versionqueue
//
//  Created by Yogesh Garg on 03/10/15.
//  Copyright (c) 2015 YogeshGarg. All rights reserved.
//

#include <iostream>
using namespace std;

#define DEBUG false

class VersionQueue {
private:
    int CAP;        // supported capacity of the version queue
    int *arr;       // This array will store *ALL* the elements in the queue
    int cVer;       // current version
    int cStart;     // current starting index
    int cEnd;       // current ending index
    int *vStart;    // store starting index of all versions
    int *vEnd;      // store ending index of all versions
    int cSize(){return 1+cEnd-cStart;}
    int vSize(int v){return 1+vEnd[v]-vStart[v];}
    void recordVersion();
public:
    VersionQueue(int s);
    ~VersionQueue();
    void enqueue(int);
    int dequeue();
    void print(int v);
    void printV(int v);
    void printC();
};

VersionQueue::VersionQueue(int s){
    CAP=s;
    arr=new int[CAP];               // Upper bound on number of enlists is s.
    cVer=-1;                        // We will have v0(init), v1, v2 and so on
    cStart=0;
    cEnd=-1;                        // Size is 0 for init
    vStart=new int[CAP];            // Upper bound on number of versions is s.
    vEnd=new int[CAP];
    recordVersion();
}

VersionQueue::~VersionQueue(){
    delete arr;
    delete vStart;
    delete vEnd;
}

void VersionQueue::recordVersion(){
    ++cVer;
    vStart[cVer]=cStart;
    vEnd[cVer]=cEnd;
}

// @desc Puts an element on the Tail and increases the version
void VersionQueue::enqueue(int val){
    if(cSize()==CAP){               // If FULL, log an error, do nothing and return
        cerr<<"Cant enqueue "<<val<<", reached capacity "<<CAP<<endl;
        return;
    }
    arr[++cEnd]=val;                // Add at incremented end
    recordVersion();                // record a new version
}

// @desc Gets the first element from the queue
int VersionQueue::dequeue(){
    if(cSize()<=0){                 // If EMPTY, log an error, do nothing and return
        cerr<<"Cant dequeue, size "<<cSize()<<endl;
        return -1;
    }
    int r=arr[cStart++];            // return element at start and increment start
    recordVersion();                // record a new version
    return r;
}

// @desc Prints the given version
void VersionQueue::printV(int v){
    if(cVer<v){                     // If VERSION DOESNT EXIST, log an error, do nothing and return
        cerr<<"Cant print, version "<<v<<" doesn't exist"<<endl;
        return;
    }
    if(DEBUG)
        cout<<"v"<<v <<" s"<<vSize(v) <<": ";
    for (int i=vStart[v]; i<=vEnd[v]; ++i) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

// @desc Prints the current version
void VersionQueue::printC(){
    printV(cVer);
}
// @desc Prints the given version
void VersionQueue::print(int v){
    printV(v);
}

int main(int argc, const char * argv[]){
    int c;
    cin>>c;
    VersionQueue vq(c);
    char com;                       // command
    int val;                        // value
    for(;c>0;--c){
        cin>>com;
        com=tolower(com);
        if('e'==com){               // (e)nqueue value
            cin>>val;
            vq.enqueue(val);
            if(DEBUG) vq.printC();
        }else if('d'==com){         // (d)equeue
            vq.dequeue();
            if(DEBUG) vq.printC();
        }else if('p'==com){         // (p)rint version
            cin>>val;
            vq.print(val);
        }                           // Else, ignore command
    }
}
int test(){

    VersionQueue vq(20);
    vq.enqueue(10);vq.printC();
    vq.enqueue(25);vq.printC();
    vq.enqueue(30);vq.printC();
    vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);vq.enqueue(40);
    vq.printC();
    
    cout<<vq.dequeue()<<endl;vq.printC();
    cout<<vq.dequeue()<<endl;vq.printC();
    cout<<vq.dequeue()<<endl;vq.printC();
    cout<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" "<<vq.dequeue()<<" ";
    vq.printC();
    cout<<vq.dequeue()<<endl;vq.printC();
    
    for(int i=0;i<50;++i){
        vq.print(i);
    }
    
    return 0;
}
