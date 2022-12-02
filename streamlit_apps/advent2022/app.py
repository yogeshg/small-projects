import streamlit as st

def func(inp):
    for line in inp.split("\n"):
        print(line)
    return "done"

def main(st):
    st.write("hello")
    inp = st.text_area("input")
    out = func(inp)
    st.write(out)


main()
