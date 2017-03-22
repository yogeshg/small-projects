//
//  main.cpp
//  flysort
//
//  Created by Yogesh Garg on 03/10/15.
//  Copyright (c) 2015 YogeshGarg. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <limits>
#include "util.h"
#include <mutex>
 

#define DEBUG false
#define QUEUE_CAPACITY 10000

std::mutex mtx;           // mutex for critical section
const long long int LONG_LONG_MAX = std::numeric_limits<long long int>::max();

class SymbolsSorter{
private:
    int num_exch;
    MyQueue* symbolsQ;
    
public:
    int willDequeue;
    SymbolsSorter(int n,int cap){
        willDequeue=-1;
        num_exch=n;
        symbolsQ= new MyQueue[num_exch];
        for(int i=0;i<num_exch;++i){
            symbolsQ[i].initMyQueue(cap);
        }
    }
    ~SymbolsSorter(){
        delete[] symbolsQ;
    }
    
    // NOT_THREAD_SAFE -- Any thread can access any other thread's queue
    // @desc Counts how many queues have min elements
    // NOTE: a queue has a min element if it is not empty
    int numMin(){
        int count=0,i=0;
        for(i=0;i<num_exch;++i){
            count+=(symbolsQ[i].size()>0);
        }
        return count;
    }
    
    bool hasMin(){
        return numMin()==num_exch;
    }
    
    // Conditional THREAD_SAFE -- Any thread can access any other thread's first element
    // Valid if it exists (to be called after hasMin)
    int getMinMinQueueNum(){
        int i=0,minIdx=-1;
        long long int candidate,runningmin;
        candidate=runningmin=LONG_LONG_MAX;
        
        for(i=0;i<num_exch;++i){
            candidate=symbolsQ[i].first();
            if((candidate<runningmin)) {
                runningmin=candidate;
                minIdx=i;
            }
        }
        return minIdx;
    }
    
    // NOT_THREAD_SAFE - Any thread can dequeue any other thread's queue, chances of error if j near i
    long long int dequeueNum(int qn){
        return symbolsQ[qn].dequeue();
    }

    // @desc Adds symbols to a thread's queue.
    // Thread safe.
    void addSymbol(int qn,long long int symbol) {
        symbolsQ[qn].enqueue(symbol);
    }
    void addEOT(int qn) {
        addSymbol(qn,LONG_LONG_MAX);
    }
    // Conditional THREAD_SAFE
    // Valid if it exists (to be called after hasMin)
    bool allEOT(){
        return getMinMinQueueNum()==-1;
    }
    
    void printQn(int qn){
        symbolsQ[qn].print();
    }
};

MyQueue* symbolsQ;

class SymbolsCollector{
public:
    static unsigned long int all[];
    static int count;
    //count=0;
    void saveSymbol(unsigned long int s){
        all[count++]=s;
    }
    void printAll(){
        std::cout<<"Tot:"<<count<<std::endl;
        for(int i=0;i<count;++i)
            std::cout<<all[i]<<" ";
        std::cout<<std::endl;
    }
};

unsigned long int SymbolsCollector::all[1000];
int SymbolsCollector::count=0;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

struct thread_data{
    int thread_id;      // Thread id of a thread
    int socketfd;       // File discriptor a thread is supposed handle
    SymbolsSorter* ss;  // Shared object between the threads
};

void *ServeExchange(void* threadArgs){
    const int MSGLEN=12;
    const int BUFLEN=256;

    int tid;
    int newsockfd;
    ssize_t n;
    bool newItemReady=false;
    bool toBeDequeued=true;
    
    unsigned int exchid=1;              // 4 bytes
    unsigned long int symbol=1;         // 8 bytes
    unsigned char mBuffer[MSGLEN];      // 12 bytes
    char cBuffer[BUFLEN];

    struct thread_data *threadData;

    // SymbolsCollector sc;
    SymbolsSorter *ss;
    
    threadData = (struct thread_data *) threadArgs;
    tid = threadData->thread_id;
    newsockfd = threadData->socketfd;
    ss = threadData->ss;

    if(DEBUG){
        std::cout << "Thread ID : " << tid << std::endl;
        std::cout << "newsockfd : " << newsockfd << std::endl;
    }
    while(symbol!=0) {                      // For each symbol
        bzero(cBuffer,BUFLEN);
        bzero(mBuffer,MSGLEN);

        (n = read(newsockfd,cBuffer,BUFLEN-1));
        if (n < 0) error("ERROR reading from socket");
        
        for (int p=0; p<n/12; ++p) {
            bcopy(cBuffer+12*p, mBuffer, 12);
            exchid=(unsigned int)bytes2int(mBuffer, 4);
            symbol=(unsigned long int)bytes2int(mBuffer+4,8);
            
            if(/* DISABLES CODE */ (false)){
                std::cout<<"In: "<<threadData->thread_id<<std::endl;
                std::cout<<"cbuff   :"<<cBuffer<<std::endl;
                std::cout<<"n       :"<<n<<std::endl;
                std::cout<<"p       :"<<p<<std::endl;
                std::cout<<"n%12    :"<<n/12<<std::endl;
                std::cout<<"coded   :";printBytes(mBuffer, 12);
                std::cout<<"decoded :"<<exchid<<" "<<symbol<<std::endl;
                if(0==symbol)
                    std::cout<<"End of Transmission"<<std::endl;
            }
            if(DEBUG){
                std::cout<<"t"<<threadData->thread_id<<" ";
                std::cout<<"e"<<exchid<<" s"<<symbol<<std::endl;
                if(0==symbol)
                    std::cout<<"End of Transmission"<<std::endl;
            }
            
            if(0!=symbol) {
                ss->addSymbol(tid, symbol);

                mtx.lock();
                // sc.saveSymbol(symbol);
                mtx.unlock();
                
            } else { // 0==symbol
                ss->addEOT(tid);
            }
            
            newItemReady=true;
            toBeDequeued=true;

            while(newItemReady){
                mtx.lock();
                newItemReady=ss->hasMin();
                mtx.unlock();
                newItemReady = newItemReady && not ss->allEOT();
                
                mtx.lock();
                toBeDequeued=(ss->willDequeue==-1);
                if(toBeDequeued) {
                    ss->willDequeue=tid;
                }
                mtx.unlock();

                if(newItemReady&&toBeDequeued){
                    int qn=ss->getMinMinQueueNum();
                    if(DEBUG) {
                        std::cout<<"Next Min discovered at "<<qn<<":";
                    }
                    // Only thing to print in Prod
                    mtx.lock();
                    std::cout << ss->dequeueNum(qn) << " ";
                    std::cout.flush();
                    mtx.unlock();
                    
                    if(DEBUG) {
                        std::cout<<std::endl;
                    }
                    
                }
                mtx.lock();
                if(toBeDequeued) {
                    ss->willDequeue=-1;
                }
                mtx.unlock();

            }

        }


    }

    close(newsockfd);
    pthread_exit(NULL);
}

int runServer(const int PORTNO,const int NUM_EXCH){
    pthread_t threads[NUM_EXCH];
    struct thread_data td[NUM_EXCH];
    
    SymbolsSorter ss(NUM_EXCH, QUEUE_CAPACITY);

    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
                            // A sockaddr_in is a structure containing an internet address
    int rc;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);       // Open Stream(TCP) Socket on Internet
    if (sockfd < 0)
        error("Error while opening socket");

    // Standard Steps for setting an address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;                 // On the Internet
    serv_addr.sin_addr.s_addr = INADDR_ANY;         // Addr of the machine
    serv_addr.sin_port = htons(PORTNO);             // Host to Network byte order
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    for(int i=0;i<NUM_EXCH;++i){
        // [crickets ...] We wait for exchanges to connect here.
        newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        td[i].socketfd=newsockfd;
        td[i].thread_id=i;
        td[i].ss=&ss;
        
        if(DEBUG)
            std::cout << "main() : creating thread, "<< i << std::endl;
        rc = pthread_create(&threads[i], NULL,
                            ServeExchange, (void *)&td[i]);
        if (rc)
            error("Error:unable to create thread,");
    }

    close(sockfd);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (3!=argc)
        error(("usage: "+std::string(argv[0])+" port num_exchange").c_str());
    runServer(atoi(argv[1]),atoi(argv[2]));
    return 0;
}

int test(int argc, char *argv[]) {
    runServer(20301,2);

    return 0;
}
