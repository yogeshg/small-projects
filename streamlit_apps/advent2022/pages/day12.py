
import sys
import os
from pprint import pprint

def noop(*_):
    return


# print = noop



class DUJ:

    class Node:
        def __init__(self, x):
            self.x = x
            self.parent = None
        def __repr__(self):
            return f"{self.x} --> {self.parent is not None}"

    def __init__(self, elems):
        self.nodes = {x: DUJ.Node(x) for x in elems}

    def join(self, x, y):
        assert x != y
        m = self.nodes[x]
        n = self.nodes[y]
        if m.parent is not None and n.parent is None:
            n.parent = m.parent
        elif n.parent is not None and m.parent is None:
            m.parent = n.parent
        elif m.parent == n.parent == None:
            n.parent = m
        elif m.parent == n.parent:
            pass
        else: # both have distinct parents
            assert m.parent is not None and n.parent is not None, f"should be node: {(m.parent, n.parent)}"
            self.join(m.parent.x, n.parent.x)

    def setid(self, x):
        curr = self.nodes[x]
        # print(f"setid?{curr}")
        while curr.parent != None and curr.parent != curr:
            curr = curr.parent
            # print(f"setid?{curr}")
        # curr.parent == None
        return curr.x





def val(x):
    if x == "S":
        return 0
    elif x == "E":
        return 25
    elif x.lower() == x:
        return ord(x) - ord('a')
    else:
        raise ValueError(f"{x} unexpected")

class Graph:
    def __init__(self, inp):
        self.m = len(inp)
        self.n = len(inp[0])
        self.grid = [[val(cell) for cell in row] for row in inp]
        self.start = None
        self.end = None
        for i,row in enumerate(inp):
            for j,cell in enumerate(row):
                if cell == "S":
                    self.start = (i,j)
                if cell == "E":
                    self.end = (i,j)

    def children(self, x, y, fwd):
        assert 0 <= x < self.m
        assert 0 <= y < self.n
        children = []
        # up
        if x > 0 and self._check(fwd,x,y,x-1,y):
            children.append((x-1, y))
        # left
        if y > 0 and self._check(fwd,x,y,x,y-1):
            children.append((x, y-1))
        if x < self.m-1 and self._check(fwd,x,y,x+1,y):
            children.append((x+1, y))
        if y < self.n-1 and self._check(fwd,x,y,x,y+1):
            children.append((x, y+1))

        if fwd:
            children.sort(key=lambda xy: (-self.grid[xy[0]][xy[1]], d(xy, self.end)))
        else:
            children.sort(key=lambda xy: (self.grid[xy[0]][xy[1]], d(xy, self.end)))  # TODO: confirm
        return children

    def __repr__(self):
        return f"M({self.m}, {self.n}, {self.start}, {self.end})"

    def _check(self, fwd, x0, y0, x1, y1):
        if fwd:
            return self.grid[x1][y1] <= self.grid[x0][y0]+1
        else:
            return self.grid[x0][y0] <= self.grid[x1][y1]+1  ## TODO: confirm
            # raise NotImplemented("NYI")

def d(a,b):
    x1,y1 = a
    x2,y2 = b
    return (x1-x2)**2 + (y1-y2)**2

def rec(g, node, allowed_depth, visited, curr_depth, fwd, path_so_far, path_map):
    # print(f"rec: {node}, {allowed_depth}, {len(visited)}, {curr_depth}, {fwd}")
    target = g.end if fwd else g.start
    if node == target:
        print(f"rec: {node}, {allowed_depth}, {len(visited)}, {curr_depth}")
        return True, curr_depth
    elif curr_depth >= allowed_depth:
        return False, -1
    children = g.children(*node, fwd)
    if len(children) == 0 or all(c in visited for c in children):
        return False, -1
    visited.add(node)
    curr_path = path_so_far + [node]
    if node not in path_map:
        path_map[node] = (curr_depth, curr_path)
    else:
        prev_depth, _ = path_map[node]
        if prev_depth > curr_depth:
            path_map[node] = (curr_depth, curr_path)

    found = False
    found_depth = allowed_depth+1
    for c in children:
        if c not in visited:
            found_curr, found_depth_curr = rec(g, c, allowed_depth, visited, curr_depth+1, fwd, curr_path, path_map)
            if found_curr and found_depth_curr < found_depth:
                found = True
                found_depth = found_depth_curr
    visited.remove(node)
    if found:
        print(f"rec: {node}, {allowed_depth}, {len(visited)}, {curr_depth}")
        return found, found_depth
    return False, -1


class MetaNode:
    def __init__(self, parent, nodes, children):
        self.parent = parent
        self.nodes = nodes
        x = sum(xy[0] for xy in nodes) / len(nodes)
        y = sum(xy[1] for xy in nodes) / len(nodes)
        self.avg = (x,y)

        self.children = children

    def __repr__(self):
        avg = "(%0.2f,%0.2f)" % self.avg
        return f"MN({avg}, {self.nodes} / {self.parent})"

class MetaGraph:

    def __init__(self, graph, duj):
        self.nodes = set()
        self.graph = graph
        self.duj = duj

    def add_node(self, parent, nodes):
        nodes = set(nodes)
        children = set()
        for node in nodes:
            for child in self.graph.children(node[0], node[1], True):
                if child in nodes:
                    continue
                childs_setid = self.duj.setid(child)
                children.add(childs_setid)
        node = MetaNode(parent, nodes, children)
        self.nodes.add(node)

    def children(self, node):
        assert node in self.nodes
        return node.children

    def print(self):
        for node in self.nodes:
            print(f"({node}")
            print(f"{self.children(node)}")



def func(inp, mode=1, debug=False):
    g = Graph(inp)
    print(g)

    nodeids = []
    for i in range(g.m):
        for j in range(g.n):
            nodeids.append((i,j))
    duj = DUJ(nodeids)
    

    for i in range(g.m):
        for j in range(g.n):
            children = g.children(i,j,True)
            for cx,cy in children:
                if g.grid[cx][cy] == g.grid[i][j]:
                    duj.join((i,j), (cx, cy))

    META_NODES = dict()
    for i in range(g.m):
        # row = ""
        for j in range(g.n):
            s = duj.setid((i,j))
            if s not in META_NODES:
                META_NODES[s] = list()
            META_NODES[s].append((i,j))
        # print(row)
    pprint(META_NODES)
    mg = MetaGraph(g, duj)
    for k, v in META_NODES.items():
        mg.add_node(k, v)

    mg.print()



    META_NODES2 = dict()
    for k,v in META_NODES.items():
        k2x = sum(xy[0] for xy in v) / len(v)
        k2y = sum(xy[1] for xy in v) / len(v)
        META_NODES2[(k2x, k2y)] = v
        print(f"({k2x:0.03}, {k2y:0.03}):     {v}")

    return



    for depth in range((g.m+g.n),g.m*g.n,10):

        # Part 1: Do forward search
        visited = set()
        path_so_far = []
        fwd_map = dict()  # (i,j) --> (steps, path)
        found, found_depth = rec(g, g.start, depth, visited, 0, True, path_so_far, fwd_map)
        # pprint({k: v[0] for k,v in fwd_map.items()})
        print(f"forward found: {found}, found_depth: {found_depth}, depth: {depth}")
        if found:
            return found_depth

        # Part 2: Do reverse search
        visited = set()
        path_so_far = []
        bkw_map = dict()  # (i,j) --> (steps, path)
        found, found_depth = rec(g, g.end, depth, visited, 0, False, path_so_far, bkw_map)
        # pprint({k: v[0] for k,v in bkw_map.items()})
        print(f"backward found: {found}, found_depth: {found_depth}, depth: {depth}")
        if found:
            return found_depth

        # Part 3: bi-directional
        found = False
        found_len = 1000000000000000000000000
        for node, (fwd_steps, fwd_path) in fwd_map.items():
            if node not in bkw_map:
                continue
            else:
                bkw_steps, bkw_path = bkw_map[node]
                steps = fwd_steps + bkw_steps
                path = fwd_path + list(reversed(bkw_path))
                found = True
                found_len = min(found_len, steps)
                print(f"may be found: {node}, {steps}, {path}")
                print(f"{fwd_steps}, {bkw_steps}, {fwd_path}, {bkw_path}")
        if found:
            return found_len

    # stack = []
    # stack.append(g.start)
    # while len(stack):
    #     curr = stack.pop()
    #     children = g.children(*curr)
    #     if len(children) == 0:

    return g

def main():
    inp = []
    for x in sys.stdin:
        inp.append(x.strip("\n"))
    x = func(inp)
    sys.stdout.write(f"{x}\n")

main()



# Sabqponm
# abcryxxl
# accszExk
# acctuvwj
# abdefghi
