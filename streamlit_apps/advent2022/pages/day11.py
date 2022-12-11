import sys
import os


class Monkey:
    def __init__(self):
        self.id = None
        self.items = []
        self.operation = None
        self.test_div = None
        self.test_true = None
        self.test_false = None
        self.operation_desc = None
        self.inspection_counter = 0

    def __repr__(self):
        return f"M({self.id}, {self.items}, {self.operation}, {self.operation_desc}, "+\
        f"{self.test_div}, {self.test_true}, {self.test_false})"

def noop(*_):
    return

def after_prefix(inp, pref):
    assert inp.startswith(pref)
    return inp.split(pref)[1]

def eval_func(lhs, op, rhs, old):
    # print(f"    eval_func{(lhs, op, rhs, old)}")
    if lhs == "old":
        lhs = old
    else:
        lhs = int(lhs)
    if rhs == "old":
        rhs = old
    else:
        rhs = int(rhs)
    if op == "*":
        return lhs * rhs
    elif op == "+":
        return lhs + rhs
    raise ValueError(f"eval_func{(lhs, op, rhs, old)}")

def eval_func_creator(lhs, op, rhs):
    return lambda old: eval_func(lhs, op, rhs, old)

def func(inp, mode=1, debug=False):

    monkeys = [Monkey(),]
    i = 0
    BIG_M = 1
    while i < len(inp):
        l = inp[i]
        if l == "":
            monkeys.append(Monkey())
        elif l[:7] == "Monkey ":
            monkeys[-1].id = int(l[7:-1])

            i+=1; l = inp[i]
            ll = after_prefix(l, "  Starting items: ")
            monkeys[-1].items = [int(x) for x in ll.split(", ")]

            i+=1; l = inp[i]
            ll = after_prefix(l, "  Operation: new = ")
            lhs, op, rhs = ll.split(" ")
            monkeys[-1].operation_desc = ll
            # monkeys[-1].operation = lambda old: eval(ll)
            monkeys[-1].operation = eval_func_creator(lhs, op, rhs)

            i+=1; l = inp[i]
            ll = after_prefix(l, "  Test: divisible by ")
            monkeys[-1].test_div = int(ll)
            BIG_M *= int(ll)

            i+=1; l = inp[i]
            ll = after_prefix(l, "    If true: throw to monkey ")
            monkeys[-1].test_true = int(ll)

            i+=1; l = inp[i]
            ll = after_prefix(l, "    If false: throw to monkey ")
            monkeys[-1].test_false = int(ll)

            # print(monkeys[-1])
            
        i+=1

    for round in range(10000):
        print(f"{round}")
        for m in monkeys:
            while len(m.items):
                m.inspection_counter += 1
                item = m.items.pop(0)
                # print(f"  Monkey inspects an item with a worry level of {item}.")
                item = m.operation(item)
                # print(f"    Worry level is {m.operation_desc} to {item}.")

                # item //= 3
                # print(f"    Monkey gets bored with item. Worry level is divided by 3 to {item}.")
                item %= BIG_M

                if 0 == (item % m.test_div):
                    mid = m.test_true
                    status = "divisible"
                else:
                    mid = m.test_false
                    status = "not divisible"
                monkeys[mid].items.append(item)
                # print(f"    Current worry level is {status} by {m.test_div}.")
                # print(f"    Item with worry level {item} is thrown to monkey {mid}.")

    ctrs = [(m.inspection_counter, m.id) for m in monkeys]
    print(ctrs)
    ctrs.sort()
    print(ctrs)
    mb = ctrs[-2][0] * ctrs[-1][0]

    return mb

def main():
    inp = []
    for x in sys.stdin:
        inp.append(x.strip("\n"))
    x = func(inp)
    sys.stdout.write(f"{x}\n")

main()

