#!/usr/bin/python2.7

import threading
import time
import sys

THREAD_COUNT = 3
PRINT_COUNT = 3

def sample(name):
    for i in range(PRINT_COUNT):
        time.sleep(0.1)
        # print name
        print QUEUE.dequeue()
    return 1

class MyQ():
    def __init__(self):
        self.queue = []
        return

    def enqueue(self, v):
        self.queue.append(v)
        return

    def dequeue(self):
        v = self.queue[0]
        time.sleep(0.00001)
        self.queue = self.queue[1:]
        return v

class Printer(threading.Thread):
    def run(self):
        sample(self.getName())
        return

QUEUE = MyQ()

def main():
    t = []
    [QUEUE.enqueue(x) for x in 'hello_world']
    print QUEUE.queue
    for i in range(THREAD_COUNT):
        t.append( Printer() )
    print "Running for the threads"
    for i in range(THREAD_COUNT):
        t[i].start()
    print "Waiting for the threads"
    for i in range(THREAD_COUNT):
        t[i].join()
    return

if __name__ == '__main__':
    main()
