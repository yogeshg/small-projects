import streamlit as st

def is_win(they, you):
    if they == "A" and you == "Y":
        return 6
    if they == "B" and you == "Z":
        return 6
    if they == "C" and you == "X":
        return 6
    if they == "A" and you == "Z":
        return 0
    if they == "B" and you == "X":
        return 0
    if they == "C" and you == "Y":
        return 0
    return 3

def value(you):
    return dict(X=1,Y=2,Z=3)[you]

def func(inp):
    score = 0
    for line in inp.split("\n"):
        they, you = line.split()
        score_round = is_win(they, you)
        score_shape = value(you)
        curr_score = score_shape + score_round
        score += curr_score

    return dict(
        a1=score,
        a2=0,
    )

# score_shape = 1, 2, 3
# score_round = 0, 3, 6
# 

def main(st):
    inp = st.text_area("input")
    out = func(inp)
    st.write(out)


main(st)
