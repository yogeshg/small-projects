import streamlit as st

SAMPLE = """vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw"""


P = {
  a: i+1
  for i,a in enumerate("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
}

def func(inp):
    tp = 0
    for i,line in enumerate(inp.split("\n")):
        n = len(line)
        c1 = set(line[:n//2])
        c2 = set(line[n//2:])
        x = list(c1.intersection(c2))
        if len(x) == 0:
            continue
        elif len(x) ==1:
            tp += P[x[0]]
        else:
            raise ValueError("x", x)


    return dict(
        a1=tp,
        a2=0,
    )

def func(inp):
    tp = 0
    tp2 = 0
    line1 = ""
    line2 = ""
    line3 = ""
    for i,line in enumerate(inp.split("\n")):
        if i%3 == 0:
            line1 = line
        elif i%3 == 1:
            line2 = line
        elif i%3 == 2:
            line3 = line
            badge = set(line1).intersection(set(line2)).intersection(set(line3))
            x = list(badge)
            if len(x) == 1:
                tp2 += P[x[0]]
            else:
                raise ValueError("x", line1, line2, line3, x)
        else:
            raise ValueError("i", i%3)

        n = len(line)
        c1 = set(line[:n//2])
        c2 = set(line[n//2:])
        x = list(c1.intersection(c2))
        if len(x) == 0:
            continue
        elif len(x) ==1:
            tp += P[x[0]]
        else:
            raise ValueError("x", x)


    return dict(
        a1=tp,
        a2=tp2,
    )

def main(st):
    inp = st.text_area("input", SAMPLE)
    out = func(inp)
    st.write(out)
    st.write("hello")


main(st)
