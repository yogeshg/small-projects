

"""

nums[-1] = -inf
nums[n] = -inf

# invariant: a peak exists in [0,n-1]


# check if n//2 is a peak -> O(3)
# if not, say left has the peak (or right, based on test)

# invariant: a peak exists in [0,n//2-1]


"""


def _is_peak(nums, n, idx):

  # base case: on edges, we have -inf
  left_is_smaller = (idx == 0)
  right_is_smaller = (idx == n-1)

  # actual check:
  if not left_is_smaller:
    left_is_smaller = nums[idx-1] < nums[idx]

  if not right_is_smaller:
    right_is_smaller = nums[idx+1] < nums[idx]

  return left_is_smaller and right_is_smaller, left_is_smaller, right_is_smaller


def _find_peak_itterative(nums,n,i,j):
  for k in range(i,j+1):
    is_peak, _, _ = _is_peak(nums, n, k)
    if is_peak:
      return k
  raise ValueError("asked to find peak in invariant breaking segment")

def _find_peak_rec(nums, n, i, j):
  # base case: search space is less than 5
  if 5 > i-j+1:
    return _find_peak_itterative(nums,n,i,j)

  # check mid
  mid = (j+1)//2

  is_peak, left_is_smaller, right_is_smaller = _is_peak(mid)

  if is_peak:
    return mid
  elif left_is_smaller:
    return _find_peak_rec(nums, n, mid+1, j)
  else:
    return _find_peak_rec(nums, n, i, mid-1)

  raise ValueError("")


def find_peak(nums):
  n = len(nums)
  return _find_peak_rec(nums, n, 0, n-1)


def main():
  nums = [1,2,3,1]
  res = find_peak(nums)
  print(res)
  print(f"{(nums,res)=}")

  nums = [1,2,3,1,0,0,0,0,0]
  res = find_peak(nums)
  print(res)
  print(f"{(nums,res)=}")

  nums = [0,0,0,0,0,0,1,2,3,1,0,0,0,0,0]
  res = find_peak(nums)
  print(res)
  print(f"{(nums,res)=}")






if __name__ == "__main__":
  main()
