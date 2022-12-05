import sys
import os



def func(inp, mode="p2", debug=False):
    instructions = []
    stacks = []
    for line in inp:
        if '[' in line:
            num_stacks = (len(line)+1) // 4
            if len(stacks) == 0:
                stacks = [[] for _ in range(num_stacks)]
            print(num_stacks) if debug else None
            for i in range(num_stacks):
                crate_id = line[4*i + 1]
                if crate_id != " ":
                    stacks[i].insert(0,crate_id)
            # add crate
        elif 'move' not in line:
            print(stacks) if debug else None
            pass # ignore numbering
        elif line == '':
            pass # ignore emptu
        else:
            _, q, _, f, _, t = line.split()
            q = int(q)
            f = int(f)
            t = int(t)
            print((q,f,t)) if debug else None
            instructions.append((q,f,t))

            if mode == "p1":
                for _ in range(q):
                    x = stacks[f-1].pop()
                    stacks[t-1].append(x)
            else:
                on_crane = stacks[f-1][-q:]
                stacks[f-1] = stacks[f-1][:-q]
                stacks[t-1] = stacks[t-1] + on_crane

            print(stacks) if debug else None
    print(stacks) if debug else None
    a1 = "".join(x[-1] for x in stacks)


    return a1

def main():
    inp = []
    for x in sys.stdin:
        inp.append(x.strip("\n"))
    x = func(inp, "p1")
    print(x)
    x = func(inp, "p2")
    print(x)

main()

