
import os
import sys

def func(inp):
  n = len(inp)
  m = len(inp[0])
  grid = [[int(x) for x in row] for row in inp]
  print(grid)
  assert m == n
  edge_count = 2*n + 2*(m-2)
  interior_count = 0
  for i in range(1,n-1):
    for j in range(1,m-1):
      x = grid[i][j]
      print("check", x)
      found = False
      # left
      left = [grid[i][jj]<x for jj in range(0,j)]
      # right
      right = [grid[i][jj]<x for jj in range(j+1, m)]
      # up
      up = [grid[ii][j]<x for ii in range(0,i)]
      # down
      down = [grid[ii][j]<x for ii in range(i+1, n)]

      found = any(all(dir_) for dir_ in (left,right,up,down))
      if found:
        interior_count += 1


      print("  left", left)
      print("  right", right)
      print("  up", up)
      print("  down", down)
      print("  found", found)
      print("  interior_count", interior_count)

  print(interior_count)
  return edge_count + interior_count



def func(inp):
  n = len(inp)
  m = len(inp[0])
  grid = [[int(x) for x in row] for row in inp]
  print(grid)
  assert m == n

  max_scenic_count = 0
  argmax_scenic_count = (None,None)
  for i in range(0,n):
    for j in range(0,m):
      print("check", grid[i][j])
      scenic_count = 0
      left = 0
      right = 0
      up = 0
      down = 0
      for jj in range(j-1,-1,-1):
        left += 1
        if grid[i][jj] >= grid[i][j]:
          break

      for jj in range(j+1,m,1):
        right += 1
        if grid[i][jj] >= grid[i][j]:
          break

      for ii in range(i-1,-1,-1):
        up += 1
        if grid[ii][j] >= grid[i][j]:
          break

      for ii in range(i+1,n,1):
        down += 1
        if grid[ii][j] >= grid[i][j]:
          break

      scenic_count = left*right*up*down
      if max_scenic_count < scenic_count:
        max_scenic_count = scenic_count
        argmax_scenic_count = (i,j)

      print("  left", left)
      print("  right", right)
      print("  up", up)
      print("  down", down)
      print("  scenic_count", scenic_count)
      print("  max_scenic_count", max_scenic_count)
      print("  argmax_scenic_count", argmax_scenic_count)



  return max_scenic_count




def main():
    inp = []
    for x in sys.stdin:
        inp.append(x.strip("\n"))
    x = func(inp)
    print(x)

main()






"""
Advent of Code[About][Events][Shop][Settings][Log Out]yogeshg 14*
  {:year 2022}[Calendar][AoC++][Sponsors][Leaderboard][Stats]
Our sponsors help make Advent of Code possible:
Panthera Investment - We solve Financial Markets. Do you want to join?
--- Day 8: Treetop Tree House ---
The expedition comes across a peculiar patch of tall trees all planted carefully in a grid. The Elves explain that a previous expedition planted these trees as a reforestation effort. Now, they're curious if this would be a good location for a tree house.

First, determine whether there is enough tree cover here to keep a tree house hidden. To do this, you need to count the number of trees that are visible from outside the grid when looking directly along a row or column.

The Elves have already launched a quadcopter to generate a map with the height of each tree (your puzzle input). For example:

30373
25512
65332
33549
35390
Each tree is represented as a single digit whose value is its height, where 0 is the shortest and 9 is the tallest.

A tree is visible if all of the other trees between it and an edge of the grid are shorter than it. Only consider trees in the same row or column; that is, only look up, down, left, or right from any given tree.

All of the trees around the edge of the grid are visible - since they are already on the edge, there are no trees to block the view. In this example, that only leaves the interior nine trees to consider:

The top-left 5 is visible from the left and top. (It isn't visible from the right or bottom since other trees of height 5 are in the way.)
The top-middle 5 is visible from the top and right.
The top-right 1 is not visible from any direction; for it to be visible, there would need to only be trees of height 0 between it and an edge.
The left-middle 5 is visible, but only from the right.
The center 3 is not visible from any direction; for it to be visible, there would need to be only trees of at most height 2 between it and an edge.
The right-middle 3 is visible from the right.
In the bottom row, the middle 5 is visible, but the 3 and 4 are not.
With 16 trees visible on the edge and another 5 visible in the interior, a total of 21 trees are visible in this arrangement.

Consider your map; how many trees are visible from outside the grid?

To begin, get your puzzle input.

Answer: 
 

You can also [Share] this puzzle.
"""

