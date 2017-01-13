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
        self.queue = []
        self.lock = lock
        return

    def enqueue(self, v):
        if(self.lock):
            self.lock.acquire()
        q = list(self.queue)
        q.append(v)
        time.sleep(0.0001)
        self.queue = q
        if(self.lock):
            self.lock.release()
        print 'enqueued', v
        return

    def dequeue(self):
        if(self.lock): 
            self.lock.acquire()
        v = self.queue[0]
        time.sleep(0.0001)
        self.queue = self.queue[1:]
        if(self.lock):
            self.lock.release()
        print 'dequeued', v
        return v

# class Printer(threading.Thread):
#     def run(self):
#         sample(self.getName())
#         return

LOCK = threading.Lock()
QUEUE = MyQ(LOCK)

def main():
    t = []
    [QUEUE.enqueue(x) for x in 'hello_world#']
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
