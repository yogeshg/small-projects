#!/usr/bin/python3

# Dota2 Senate



# def simulate(senate):
#   N = len(senate)
#   blocked = [False for i in range(N)]
#   for i in range(N):
#     # round i
#     for j in range(1,N):
#     

NAMES = {
  "R": "Radiant",
  "D": "Dire"
}

def tide_favors(senate, N):

  favorite = senate[0]
  favorite_count = 1
  for i in range(1, N):
    senator = senate[i]
    if senator == favorite:
      favorite_count += 1
    else:
      favorite_count -= 1
    # handle tide turn
    if favorite_count < 0:
      favorite = senator
      favorite_count = 0 - favorite_count
  return NAMES[favorite]

def winner(senate):
  N = len(senate)
  if N == 0:
    return None
  is_even = ((N%2) == 0)
  num_r = 0
  for s in senate:
    if s == "R":
      num_r += 1
  num_d = N - num_r
  if num_r > N//2:
    return "Radiant"
  if num_d > N//2:
    return "Dire"

  # even and same
  assert is_even
  assert num_r == num_d

  # return simulate(senate, N)

  return tide_favors(senate, N)

def main():
  print(winner("RD"), "R?")
  print(winner("RDD"), "D?")
  print(winner("RDDR"), "D?")
  print(winner("RDDDRR"), "D?")
  print(winner("RDDRRD"), "R?")


main()
