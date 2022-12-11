import sys
import os
import math

DIRS = {
    "L": (0, -1),
    "R": (0, 1),
    "U": (-1, 0),
    "D": (1, 0),
}

def abs(x):
    return x if x>=0 else -x

def tailmove(tail, head):
    debug = head == (-2, 1)
    debug = False
    x0,y0 = tail
    x1,y1 = head
    dx = x1-x0
    dy = y1-y0
    # print(f"dx,dy: {(dx,dy)} <= {tail}-{head}")
    if debug:
        print(f"{abs(dx) <= 1 and abs(dy) <= 1}")
    if abs(dx) <= 1 and abs(dy) <= 1:
        return x0, y0
    if abs(dx) > 2 and abs(dy) > 2:
        raise ValueError(f"{(x0,y0)} ---diagonal(>=2)---> {x1,y1}")

    incrx = 0
    if dx > 0:
        incrx = 1
    if dx < 0:
        incrx = -1
    incry = 0
    if dy > 0:
        incry = 1
    if dy < 0:
        incry = -1
    return (x0+incrx, y0+incry)


def func(inp):
    knots = [(0,0) for _ in range(10)]
    all_tail_moves = set()
    for step in inp:
        dir_, ct = step.split()
        print(dir_, ct)
        ct = int(ct)
        assert dir_ in DIRS
        dx, dy = DIRS[dir_]
        for _ in range(ct):
            knots[0] = knots[0][0]+dx, knots[0][1]+dy
            for i in range(1,10):
                # head = knots[i-1]
                # tail = knots[i]
                # head = (head[0]+dx, head[1]+dy)
                knots[i] = tailmove(knots[i], knots[i-1])
            all_tail_moves.add(knots[-1])
            # print("  ", knots)
            print(len(all_tail_moves))
        print(knots)
    return len(all_tail_moves)


def main():
    inp = []
    for x in sys.stdin:
        inp.append(x.strip("\n"))
    x = func(inp)
    print("a:", x)

main()