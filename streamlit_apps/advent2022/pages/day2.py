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

def is_win2(they, outcome):
    return dict(X=0, Y=3, Z=6)[outcome]

def value2(they, outcome):
    return dict(
        A=dict(
            X=3,  # rock, loss -> scissor -> 3
            Y=1,  # rock, draw -> rock -> 1
            Z=2,  # rock, win -> paper -> 2
            ),
        B=dict(
            X=1,  # paper, loss -> rock -> 1
            Y=2,  # paper, draw -> paper -> 2
            Z=3,  # paper, win -> sciros -> 3
            ),
        C=dict(
            X=2,  # scissor, loss -> paper -> 2
            Y=3,  # scissor, draw -> scissor -> 3
            Z=1,  # scissor, win -> rock -> 1
            ),
    )[they][outcome]

def func1(inp):
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

def func2(inp):
    score = 0
    for line in inp.split("\n"):
        they, you = line.split()
        score_round = is_win2(they, you)
        score_shape = value2(they, you)
        curr_score = score_shape + score_round
        score += curr_score

    return dict(
        a1=0,
        a2=score,
    )

# score_shape = 1, 2, 3
# score_round = 0, 3, 6
# 

def main(st):
    inp = st.text_area("input")
    out = func2(inp)
    st.write(out)


main(st)
