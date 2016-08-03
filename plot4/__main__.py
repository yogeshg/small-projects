#!/usr/bin/python
import sys
from __init__ import *

def main():
    try:
        player1 = int(sys.argv[1])
        player2 = int(sys.argv[2])
    except:
        print "usage:\n\t{} player1 player2".format(sys.argv[0])
        sys.exit(1)
    GameCl(10).play(player1=player1, player2=player2)

if __name__ == '__main__':
    main()

