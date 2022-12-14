
import sys
import os
from pprint import pprint
import time

def noop(*_):
    return



def add_one(dd,x,y,t):
    dd[(x,y)] = t

def sign(x):
    return -1 if x<0 else 1

def add_line(dd, p0, p1, t):
    x0, y0 = p0
    x1, y1 = p1
    if y1 == y0:
        s = sign(x1-x0)
        for x in range(x0,x1,s):
            add_one(dd, x+s, y1, t)
    elif x1 == x0:
        s = sign(y1-y0)
        for y in range(y0,y1,s):
            add_one(dd, x1, y+s, t)
    else:
        raise ValueError(f"can not add_line{(dd, p0, p1, t)}")





M = 1000000000000000000000000000000000000000000000000000000000000000000000000000000000000

class Cave:

    def __init__(self, inp):
        self.grid = dict()
        self.xmax = -1
        self.xmin = M
        self.ymax = -1
        self.ymin = M
        for row in inp:
            cells = row.split(" -> ")
            x0,y0 = cells[0].split(",")
            x0,y0 = int(x0), int(y0)
            add_one(self.grid, x0, y0, "#")
            self.xmax = max(self.xmax, x0)
            self.xmin = min(self.xmin, x0)
            self.ymax = max(self.ymax, y0)
            self.ymin = min(self.ymin, y0)
            for i in range(1, len(cells)):
                x1,y1 = cells[i].split(",")
                x1,y1 = int(x1), int(y1)
                add_line(self.grid, (x0,y0), (x1,y1), "#")
                x0,y0 = x1,y1
                self.xmax = max(self.xmax, x0)
                self.xmin = min(self.xmin, x0)
                self.ymax = max(self.ymax, y0)
                self.ymin = min(self.ymin, y0)

        floory = self.ymax + 2
        floorx1 = self.xmin - floory - 10
        floorx2 = self.xmax + floory + 10
        add_line(self.grid, (floorx1-1,floory), (floorx2,floory), "#")
        self.xmax = max(self.xmax, floorx2)
        self.xmin = min(self.xmin, floorx1)
        self.ymax = max(self.ymax, floory)
        self.ymin = min(self.ymin, 0)



    def print(self):
        # return
        for y in range(self.ymin, self.ymax+1):
            row = ""
            for x in range(self.xmin, self.xmax+1):
                row += self.grid.get((x,y), ".")
            print(row)
        print()



def func(inp):
    c = Cave(inp)



    c.print()
    # pprint(c.xmax)
    # pprint(c.xmin)
    # pprint(c.ymax)
    # pprint(c.ymin)

    count_sand = 0
    while True and (500,0) not in c.grid:
        sandx = 500
        y = 0 #c.ymin
        while y < c.ymax+1:
            # print(f"  {y}")
            if (sandx,y) not in c.grid:
                y += 1
                continue
            elif (sandx-1,y) not in c.grid:
                sandx -= 1
                continue
            elif (sandx+1,y) not in c.grid:
                sandx += 1
                continue
            elif (sandx,y) in c.grid and (sandx+1,y) in c.grid and (sandx-1,y) in c.grid:
                # cant move further
                count_sand += 1
                add_one(c.grid, sandx, y-1, "o")
                break
            else:
                raise ValueError("shrugs")
        # print(y)
        if y > c.ymax:
            print(f"I want to break free!!!")
            break
        # print(count_sand)
        
        if count_sand % 50 == 0:
            c.print()
            time.sleep(0.05)
    return count_sand







def main():
    inp = []
    for x in sys.stdin:
        inp.append(x.strip("\n"))
    x = func(inp)
    sys.stdout.write(f"{x}\n")

main()

