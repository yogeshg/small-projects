import sys
import os
import math


def check(count, cycle, x, screen):

    if x == (cycle-1)%40 or x+1 == (cycle-1)%40 or x-1 == (cycle-1)%40:
        screen[(cycle-1)//40][(cycle-1)%40] = "#"
    if ((cycle - 20) % 40) == 0:
        return count+cycle*x
    return count

def func(inp):
    cycle = 0
    x = 1

    # instr == "noop"
    # i = 0
    # while True:
    #     cycle+=1

    #     if instr == "noop":
    #         instr = inp[i]
    #         i+=1
    #         instr = instr.split()
    #         cmd = instr[0]
    #         args = instr[1:]
    screen = [["." for x in range(40)] for y in range(6)]

    count = 0
    for st in inp:
        if st == "":
            break
        cycle += 1
        count = check(count, cycle, x, screen)

        st = st.split()
        cmd = st[0]
        args = st[1:]
        if cmd == "noop":
            pass
        elif cmd == "addx":
            cycle += 1
            count = check(count, cycle, x, screen)
            x += int(args[0])
            pass
        print(st)
    for row in screen:
        print("".join(row))
    return count


def main():
    inp = []
    for x in sys.stdin:
        inp.append(x.strip("\n"))
    x = func(inp)
    print("a:", x)

main()