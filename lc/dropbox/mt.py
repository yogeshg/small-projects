#!/usr/bin/python2.7

import threading
import time
import sys

THREAD_COUNT = 3
PRINT_COUNT = 3

def sample(name):
    for i in range(PRINT_COUNT):
        time.sleep(0.1)
        v = QUEUE.dequeue()
        print name, v
        QUEUE.enqueue(v)
    return 1

class MyQ():
    def __init__(self, lock=None):
        self.buffer_size = 20
        self.queue = ['#']*self.buffer_size
        self.start = 0
        self.size = 0
        self.lock = lock
        return

    def length():
        return self.size

    def enqueue(self, v):

        if(self.lock):
            self.lock.acquire()
        p = self.start + self.size
        self.size+=1
        time.sleep(0.0001)
        if(self.lock):
            self.lock.release()
        self.queue[(p)%20] = v

        # print 'enqueued', v, 'at', p
        return

    def dequeue(self):
        if(self.size > 0):
            if(self.lock):
                self.lock.acquire()
            s = self.start
            self.start+=1
            self.size-=1
            if(self.lock):
                self.lock.release()
            v = self.queue[s]
        self.queue[s]='#'
        return v

LOCK = threading.Lock()
QUEUE = MyQ(LOCK)

def main():
    t = []
    [QUEUE.enqueue(x) for x in 'hello_world!']
    print QUEUE.queue
    for i in range(THREAD_COUNT):
        t1 = threading.Thread( target=sample, args=("T"+str(i),) )
        t.append( t1 )
    print "Running for the threads"
    for i in range(THREAD_COUNT):
        t[i].start()
    print "Waiting for the threads"
    for i in range(THREAD_COUNT):
        t[i].join()
    print QUEUE.queue
    return

if __name__ == '__main__':
    main()
