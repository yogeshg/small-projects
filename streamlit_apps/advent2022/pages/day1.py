import streamlit as st

SAMPLE = """
1000
2000
3000

4000

5000
6000

7000
8000
9000

10000
"""

def func(inp):
    all_cals = []
    curr_cal = 0
    for i,line in enumerate(inp.split("\n")):
        if line == "":
            all_cals.append(curr_cal)
            curr_cal = 0
        else:
            cal = int(line)
            curr_cal += cal
    all_cals.sort()
    return dict(
        a1=all_cals[-1],
        a2=sum(all_cals[-3:]),
    )

def main(st):
    inp = st.text_area("input", SAMPLE)
    out = func(inp)
    st.write(out)


main(st)
