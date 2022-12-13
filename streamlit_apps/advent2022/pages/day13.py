import sys
import os


def noop(*_):
    return


def cmp1(x,y):
    print(f"cmp1{(x,y)}")
    if x < y:
        return "YES"
    elif y < x:
        return "NO"
    return "MAYBE"

def cmp2(x,y):
    print(f"cmp2{(x,y)}")
    i = 0
    while i < len(x) and i < len(y):
        r = cmp3(x[i], y[i])
        if r in ("YES", "NO"):
            return r
        # r is may be, so continue
        i += 1

    if len(y) != i:
        return "YES"
    if len(x) != i:
        return "NO"
    return "MAYBE"

def cmp3(x, y):
    if isinstance(x, int) and isinstance(y, int):
        return cmp1(x,y)
    if isinstance(x, list) and isinstance(y, list):
        return cmp2(x, y)
    if isinstance(x, list):
        return cmp2(x, [y])
    if isinstance(y, list):
        return cmp2([x], y)
    raise ValueError(f"missed condition: {(x,y)}")


def func(inp, mode=1, debug=False):
    idx = 0
    lines_read = 0
    out = 0
    while lines_read < len(inp):
        idx += 1

        a = inp[lines_read]
        a = eval(a)
        lines_read+=1
        b = inp[lines_read]
        b = eval(b)
        lines_read+=1
        assert lines_read == len(inp) or "" == inp[lines_read]
        lines_read+=1

        # print(idx)
        # print(a)
        # print(b)

        res = cmp3(a,b)
        assert res in ("YES", "NO")

        if res == "YES":
            out += idx


    return out


def main():
    inp = []
    for x in sys.stdin:
        inp.append(x.strip("\n"))
    x = func(inp)
    sys.stdout.write(f"{x}\n")

main()

