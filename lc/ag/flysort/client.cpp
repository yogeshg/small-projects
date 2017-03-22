//
//  client.cpp
//  hw
//
//  Created by Yogesh Garg on 03/10/15.
//  Copyright (c) 2015 YogeshGarg. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "util.h"

#define DEBUG false

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    const int MSGLEN=12;
    const int BUFLEN=256;
    
    int sockfd, portno;
    ssize_t n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    unsigned int exchid=1;              // 4 bytes
    unsigned long int symbol=1;         // 8 bytes
    unsigned char mBuffer[MSGLEN];      // 12 bytes
    char cBuffer[BUFLEN];

    if (argc < 4) {
        error(("usage: "+std::string(argv[0])+" hostname port exchid file").c_str());
    }
    exchid = (unsigned int) atol(argv[3]);
    freopen(argv[4], "r", stdin);
    
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
    while(symbol!=0) {                      // For each symbol
        bzero(cBuffer,BUFLEN);
        bzero(mBuffer,MSGLEN);
        fgets(cBuffer,BUFLEN-1,stdin);        // read from stdin
        symbol=atol(cBuffer);               // parse to long (8) bits
        int2bytes(exchid, mBuffer, 4);      // write exchid in the first 4 bytes
        int2bytes(symbol, mBuffer+4, 8);    // write symbol in the next 8 bytes
        if(DEBUG){
            std::cout<<"cbuff   :"<<cBuffer<<std::endl;
            std::cout<<"vals    :"<<exchid<<" "<<symbol<<std::endl;
            std::cout<<"coded   :";printBytes(mBuffer, 12);
            std::cout<<"decoded :"<<bytes2int(mBuffer, 4)<<" "<<bytes2int(mBuffer+4,8)<<std::endl;
        }
        n=write(sockfd, mBuffer, 12);
        if (n < 0)
            error("ERROR writing to socket");
        sleep(random()%2);
    }
    close(sockfd);
    return 0;
}
