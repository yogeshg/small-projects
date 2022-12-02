import streamlit as st

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
        a1=all_cals[-1:],
        a2=sum(all_cals[-3:]),
    )

def main(st):
    st.write("hello")
    inp = st.text_area("input")
    out = func(inp)
    st.write(out)


main(st)
