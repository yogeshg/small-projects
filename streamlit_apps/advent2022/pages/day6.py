import sys
import os



def func(inp, mode=4, debug=False):
    mem = ['_' for _ in range(mode)]
    curr = 0
    # print(inp)
    for i,x in enumerate(inp):
        # print(curr, i, x, mem, set(mem))
        mem[curr] = x
        test = set(mem)
        ll = len(test)
        if "_" in test:
            ll -= 1
        if ll == mode:
            return i+1
        curr += 1
        curr %= mode
    return -1

def main():
    for x in sys.stdin:
        inp = x.strip("\n")
        x = func(inp)
        print(x)
        x = func(inp, 14)
        print(x)
        # x = func(inp, "p2")
        # print(x)

main()

