import streamlit as st

def func(inp):
    return dict(
        a1=0,
        a2=0,
    )

def main(st):
    inp = st.text_area("input")
    out = func(inp)
    st.write(out)


main(st)
