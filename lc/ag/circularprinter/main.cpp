//
//  main.cpp
//  circularprinter
//
//  Created by Yogesh Garg on 04/10/15.
//  Copyright (c) 2015 YogeshGarg. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include <unistd.h>

#include <string.h>

#define DEBUG false

int NUM_CHARS;
int NUM_LOOP;
int NUM_THREADS;
size_t LEN_STR;
const char *STR;
int IDX;

int cond_turn=-1;
pthread_cond_t* cond;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void error(const char *msg)
{
    std::cerr<<msg<<std::endl;
    exit(-1);
}


void *ServerFunc(void *param)
{
    long tid=(long)param;
    int rc;
    int j,k;
    
    for(j=0;j<NUM_LOOP;++j) {
        rc = pthread_mutex_lock(&mutex);
        while ( cond_turn != tid)
        {
            if(DEBUG){
                std::cout<<"Thread"<<1+tid<<" blocked"<<std::endl;
            }
            rc = pthread_cond_wait(&cond[tid], &mutex);
            if(DEBUG){
                std::cout<<"Thread"<<1+tid<<" unblocked"<<std::endl;
            }
        }
        rc = pthread_mutex_unlock(&mutex);
        
        std::cout<<"Thread"<<1+tid<<": ";
        for(k=0;k<NUM_CHARS;++k){
            std::cout<<STR[IDX];
            IDX=(IDX+1)%LEN_STR;
        }
        std::cout<<std::endl;
        
        rc = pthread_mutex_lock(&mutex);
        cond_turn = (tid+1)%NUM_THREADS ;
        rc = pthread_cond_signal(&cond[cond_turn]);
        
        rc = pthread_mutex_unlock(&mutex);
    }
    if(DEBUG){
        std::cout<<"Thread"<<1+tid<<" exiting"<<std::endl;
    }
    pthread_exit(NULL);
}

int runRoundRobin(const char *str,int numchars,int numthreads,int numloops) {
    
    long i,rc;

    void *status;
    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    cond=new pthread_cond_t[NUM_THREADS];
    
    STR=str;
    LEN_STR=strlen(STR);
    IDX=0;
    NUM_CHARS=numchars;
    NUM_LOOP=numloops;
    NUM_THREADS=numthreads;

    
    for(i=0;i<NUM_THREADS;++i){
        cond[i]=PTHREAD_COND_INITIALIZER;
    }
    cond_turn=0;

    // Initialize and set thread joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    for(i=0;i<NUM_THREADS;++i){
        rc=pthread_create(&threads[i], NULL, ServerFunc, (void *)(long)i);
        if(rc) error("Error:unable to create thread");
        if(DEBUG) {
            std::cout<<"Thread"<<1+i<<" created"<<std::endl;
        }
    }
    
    pthread_attr_destroy(&attr);
    for( i=0; i < NUM_THREADS; i++ ){
        pthread_join(threads[i], &status);
        pthread_cond_destroy(&cond[i]);
        if(DEBUG) {
            std::cout << "Main: completed thread id :" << i << "  exiting with status :" << status << std::endl;
        }
    }
    delete[] cond;
    pthread_mutex_destroy(&mutex);
    
    return 0;
}

int main(int argc, const char * argv[]) {
    if (5!=argc)
        error(("usage: "+std::string(argv[0])+" string char_count thread_count loops").c_str());
    runRoundRobin(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
}

