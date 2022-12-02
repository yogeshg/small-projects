import streamlit as st

def func(inp):
    lines = []
    for line in inp.split("\n"):
        lines.append(line)
    return lines

def main(st):
    st.write("hello")
    inp = st.text_area("input")
    out = func(inp)
    st.write(out)


main(st)
