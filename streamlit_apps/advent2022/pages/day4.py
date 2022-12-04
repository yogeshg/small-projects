import sys
import os



def func(inp):
    num_full_overlap = 0
    num_any_overlap = 0
    for line in inp:
        r1, r2 = line.split(",")
        s1,e1 = r1.split("-")
        s2,e2 = r2.split("-")
        s1,s2,e1,e2 = int(s1),int(s2),int(e1),int(e2)
        # if s1 > s2:
        #     s1,e1,s2,e2 = s2,e2,s1,e1
        assert s1 <= e1 and s2 <= e2


        if s1 <= s2 and s2 <= e1:
            num_any_overlap += 1
        elif s2 <= s1 and s1 <= e2:
            num_any_overlap += 1 

        if s1 <= s2 and e2 <= e1:
            num_full_overlap += 1
        elif s2 <= s1 and e1 <= e2:
            num_full_overlap += 1

        # l1 = ["." for _ in range(max(e1,e2)+1)]
        # l2 = ["." for _ in range(max(e1,e2)+1)]

        # for x in range(s1,e1+1):
        #     l1[x]="x"

        # for x in range(s2,e2+1):
        #     l2[x]="x"

    return num_full_overlap, num_any_overlap

def main():
    inp = []
    for x in sys.stdin:
        inp.append(x.strip())
    x = func(inp)
    print(x)

main()

