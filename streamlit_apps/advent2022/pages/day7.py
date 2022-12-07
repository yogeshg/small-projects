import sys
import os


TOTAL_SIZE = 70000000
REQRD_SIZE = 30000000


class Node:
    def __init__(self, name):
        self.name = name
        self.children = []
        self.parent = None
        self.is_dir = False
        self.is_file = False
        self.file_size = 0
        self.direct_children_size = 0
        self.total_dir_size = 0


    def children_by_name(self):
        return {x.name:x for x in self.children}

    def print_rec(self, tab=""):
        print(f"{tab}{self}")
        for c in self.children:
            c.print_rec(tab=tab+"  ")

    def find_size_rec(self):
        if self.is_file:
            return self.file_size, 0
        self.total_dir_size = 0
        curr_sum_a1 = 0
        for c in self.children:
            sz, sum_a1 = c.find_size_rec()
            self.total_dir_size += sz
            curr_sum_a1 += sum_a1
        if self.total_dir_size <= 100000:
            # print("hello", self)
            curr_sum_a1 += self.total_dir_size
        return self.total_dir_size, curr_sum_a1

    def find_minimal_rec(self, thresh):
        if self.is_file:
            return []
        elif self.total_dir_size < thresh:
            print(f"no possibilities in {self}")
            return []
        print("found some", self)
        candidate_so_far = self
        for c in self.children:
            potentials = c.find_minimal_rec(thresh)
            if len(potentials) > 0:
                print("returned")
            for p in potentials:
                if p.name == "d":
                    print("hello", p.total_dir_size)
                if p.total_dir_size < candidate_so_far.total_dir_size:
                    print("found smaller")
                    candidate_so_far = p
        else:
            print("found no better", self)
        print("returning some", self)
        return [candidate_so_far]

    def __repr__(self):
        pn = None
        if self.parent is not None:
            pn = self.parent.name
        return (
            f"Node({self.name}, {len(self.children)}, " +
            f"{pn}, " +
            f"{self.is_dir}, {self.is_file}, {self.file_size}, " +
            f"{self.direct_children_size}, {self.total_dir_size})"
        )

class St:
    def __init__(self, *args):
        self.is_cmd = False
        self.cmd = ""
        self.args = []

        a = args[0]
        if a == "$":
            self.is_cmd = True
        if self.is_cmd:
            self.cmd = args[1]
            self.args = args[2:]
        else:
            self.args = args[:]

    def __repr__(self):
        return f"St({self.is_cmd}, {self.cmd}, {self.args})"

def noop(*_):
    return

def func(inp, mode=1, debug=False):
    # print = print if debug else noop

    root = Node("/")
    root.is_dir = True

    curr_d = None

    i = 0
    ll = len(inp)
    while i < ll:
        statement = inp[i]
        st = St(*statement.split())
        # print(st)

        if st.is_cmd and st.cmd == "cd" and st.args[0] == "/":
            curr_d = root
        elif st.is_cmd and st.cmd == "cd" and st.args[0] == "..":
            assert curr_d.parent is not None
            curr_d = curr_d.parent
        elif st.is_cmd and st.cmd == "cd":
            cc = curr_d.children_by_name()
            assert st.args[0] in cc
            curr_d = cc[st.args[0]]
            assert curr_d.is_dir
        elif st.is_cmd and st.cmd == "ls":
            pass # no op for now
        elif not st.is_cmd and st.args[0] == "dir":
            node = Node(st.args[1])
            node.parent = curr_d
            node.is_dir = True
            curr_d.children.append(node)
        elif not st.is_cmd:
            node = Node(st.args[1])
            node.parent = curr_d
            node.is_file = True
            node.file_size = int(st.args[0])
            curr_d.children.append(node)
            # print(node)
            curr_d.direct_children_size += node.file_size
            print(node, node.file_size)
            print(curr_d, curr_d.direct_children_size)
        else:
            raise ValueError("whoops")


        i+=1

    root_size, sum_a1 = root.find_size_rec()
    # root.print_rec()
    
    avail = TOTAL_SIZE - root_size
    thresh = REQRD_SIZE - avail
    print(thresh)

    node = root.find_minimal_rec(thresh)

    return sum_a1, node[0].total_dir_size

def main():
    inp = []
    for x in sys.stdin:
        inp.append(x.strip("\n"))
    x = func(inp)
    print(x)

main()

