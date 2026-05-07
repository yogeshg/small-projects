import json

"""
2294. Partition Array Such That Maximum Difference Is K

You are given an integer array nums and an integer k. You may partition nums into one or more subsequences such that each element in nums appears in exactly one of the subsequences.

Return the minimum number of subsequences needed such that the difference between the maximum and minimum values in each subsequence is at most k.

A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

"""


def find_min_max(nums, above, below):
    N = len(nums)
    if N == 0:
      return (None, None)
    min_so_far = None
    max_so_far = None

    for i in range(N):
      curr = nums[i]
      if above is not None and curr <= above:
         continue
      if below is not None and curr >= below:
         continue
      if min_so_far is None or min_so_far > curr:
        min_so_far = curr
      if max_so_far is None or max_so_far < curr:
        max_so_far = curr

    return (min_so_far, max_so_far)


def count_unique(nums):
  uniq = set()
  res = 0
  for n in nums:
    if n not in uniq:
      res += 1
      uniq.add(n)
    # print(f"  {(uniq)=}")
  return res


def log2(n):
  for i in range(n+1 if n > 0 else -n):
    if n >> i == 0 or n >> i == -1:
      return n
  raise ValueError("Welp!")


def find_min_buckets_via_sorting(nums, k):
  nums.sort()
  num_buckets = 0
  curr_start = None
  curr_end = None
  for n in nums:
    if curr_start is None or (n > curr_end):
      curr_start = n
      curr_end = n+k
      num_buckets += 1
  return num_buckets


def find_min_buckets(nums, k):
    N = len(nums)
    if N == 0:
      return 0

    if k == 0:
      return count_unique(nums)

    num_buckets = 0
    curr_above = None
    curr_below = None

    while (curr_above is None and curr_below is None) or (curr_above <= curr_below):
      # print(f"  {(curr_above,curr_below)=}")
      curr_min, curr_max = find_min_max(nums, curr_above, curr_below)
      # print(f"  {(curr_min,curr_max)=}")
      if curr_max is None and curr_min is None:
        return num_buckets
      if curr_max is None or curr_max is None:
        raise ValueError("can not have only one None")
      delta = curr_max - curr_min
      # print(f"  {(delta)=}")
      if delta <= k:
        num_buckets += 1
        return num_buckets
      if log2(delta) > k:
        return find_min_buckets_via_sorting(nums, k)
      num_buckets += 2
      curr_above = curr_min + k
      curr_below = curr_max - k

    return num_buckets


def main():
  tests = (
    ([3,6,1,2,5], 2, 2),
    ([1,2,3], 1, 2),
    ([5,2,1,5,3], 3, 2),
    ([2,2,4,5], 0, 3),
    # tuple(json.loads(open("p-2294-tc-72.json", "r").read()).values()),
    tuple(json.loads(open("p-2294-tc-93.json", "r").read()).values()),
  )

  for nums, k, res in tests:
    # print(f"{(len(nums) if len(nums) > 10 else nums,k)=}")
    sol = find_min_buckets(nums,k)
    # print(f"{(res,sol)=}")
    assert res == sol

if __name__ == "__main__":
  main()


