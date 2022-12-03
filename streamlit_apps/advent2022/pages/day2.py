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

SAMPLE = """A Y
B X
C Z"""

def func2(inp):
    score1 = 0
    score2 = 0
    for line in inp.split("\n"):
        they, you = line.split()

        score_round = is_win(they, you)
        score_shape = value(you)
        curr_score = score_shape + score_round
        score1 += curr_score

        score_round = is_win2(they, you)
        score_shape = value2(they, you)
        curr_score2 = score_shape + score_round
        score2 += curr_score2

    return dict(
        a1=score1,
        a2=score2,
    )

# score_shape = 1, 2, 3
# score_round = 0, 3, 6

def main(st):
    inp = st.text_area("input", SAMPLE)
    out = func2(inp)
    st.write(out)
    data = [{"x": i, "y": i**2} for i in range(1000)]
    st.scatter(data)

main(st)
