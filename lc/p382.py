from typing import *
import random

class ListNode:
    def __init__(self, val=0, next_=None):
        self.val = val
        self.next = next_



def get_random(head: Optional[ListNode]):
  len_ = 0
  curr = head
  while curr is not None:
    len_ += 1
    curr = curr.next
  idx = random.randint(1,len_)
  # print(f"{(len_,idx)=}")
  curr = head
  while curr is not None:
    if idx == 1:
      return curr.val
    idx -= 1
    curr = curr.next


def get_random_rc(head: Optional[ListNode]):
  curr = head
  kept = None
  idx = 1
  while curr is not None:
      if random.random() < 1/float(idx):
        kept = curr.val
      curr = curr.next
      idx += 1
  return kept


def main():
  calls = ["", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
  args = [[[1, 2, 3]], [], [], [], [], []]
  [None, 1, 3, 2, 2, 3]

  head = ListNode(val=1, next_=ListNode(val=2, next_=ListNode(val=3)))
  for _ in range(10):
    a = get_random_rc(head)
    print(f"{(a)=}")


if __name__ == "__main__":
	main()
