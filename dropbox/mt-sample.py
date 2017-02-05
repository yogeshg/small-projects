#!/usr/bin/python2.7

import threading
import time
import sys

THREAD_COUNT = 3
PRINT_COUNT = 3

def sample(name):
    for i in range(PRINT_COUNT):
        time.sleep(0.1)
        print name, i
    return 1


class Printer(threading.Thread):
    def run(self):
        sample(self.getName())
        return

def main():
    t = []
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