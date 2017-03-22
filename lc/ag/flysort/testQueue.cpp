//
//  testQueue.cpp
//  hw
//
//  Created by Yogesh Garg on 04/10/15.
//  Copyright (c) 2015 YogeshGarg. All rights reserved.
//
#include<iostream>
#include"util.h"

int main(){
	MyQueue q2(16);
	MyQueue q;
	q.initMyQueue(8);

	q.print();

	for(int i=0;i<8;++i){
		q.enqueue(i*10);
		q.print();
	}

	for(int i=0;i<4;++i){
		std::cout<<"dequeue:"<<q.dequeue()<<std::endl;
		q.print();
	}

	for(int i=0;i<16;++i){
		q.enqueue(i*100);
		q.print();
	}

	for(int i=0;i<20;++i){
		std::cout<<"dequeue:"<<q.dequeue()<<std::endl;
		q.print();
	}

    return 0;
}

int main_man(){
	MyQueue q(16);
	// q.print();

	char com;
	int val;

	while(true){
		std::cin>>com;
		if('e'==com){
			std::cin>>val;
			q.enqueue(val);
		} else if('d'==com){
			std::cout<<q.dequeue()<<std::endl;
		} else if('p'==com){
			q.print();
		} else {
			break;
		}
	}
    return 0;
}
