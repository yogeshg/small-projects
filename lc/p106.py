"""
106. Construct Binary Tree from Inorder and Postorder Traversal
Medium
Topics
premium lock icon
Companies
Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.

 

Example 1:


Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: inorder = [-1], postorder = [-1]
Output: [-1]
 

Constraints:

1 <= inorder.length <= 3000
postorder.length == inorder.length
-3000 <= inorder[i], postorder[i] <= 3000
inorder and postorder consist of unique values.
Each value of postorder also appears in inorder.
inorder is guaranteed to be the inorder traversal of the tree.
postorder is guaranteed to be the postorder traversal of the tree.
"""

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def __repr__(self):
        val = self.val
        left = self.left
        right = self.right
        return f"({val=} {left=} {right=})"

    def __repr__(self):
      result = ""
      if self.left is not None:
          result += f"{self.val} --l--> {self.left.val}\n"
          result += f"{self.left}"
      if self.right is not None:
          result += f"{self.val} --r--> {self.right.val}\n"
          result += f"{self.right}"
      return result


def fill_level(node, result, level, depth):
    if level == depth:


def tree_to_list(node):
    result = []
    if root is None:
        return result

    # level order traversal
    curr_level = 1
    has_next_level = True

    while has_next_level:
        result.extend([None for _ in range((2**depth)-1)])
        has_next_level = fill_level(node, result, curr_level, 1)
        curr_level += 1



def reconstruct_tree(inorder, postorder):
    if len(inorder) != len(postorder):
        raise ValueError("Wrong input!")

    tree = reconstruct_tree_rec(inorder, postorder)

    print(f"{tree}")

    return tree_to_list(tree)

def reconstruct_tree_rec(inorder, postorder):
    if len(inorder) != len(postorder):
        raise RuntimeError("inorder and postorder lengths do not match")

    N = len(postorder)

    if N == 0:
        return []

    root = TreeNode(val=postorder[-1], left=None, right=None)

    if N == 1:
        return root

    left_len = None
    for i in range(N):
        if inorder[i] != root.val:
            continue
        left_len = i
        break

    left_subtree = reconstruct_tree_rec(
        inorder[:left_len],
        postorder[:left_len],
    )

    right_subtree = reconstruct_tree_rec(
        inorder[left_len+1:],
        postorder[left_len:-1],
    )

    root.left = left_subtree
    root.right = right_subtree

    return root


def main():
    testcases = [
        (
            [9,3,15,20,7],
            [9,15,7,20,3],
            [3,9,20,None,None,15,7],
        ),
    ]


    for inorder, postorder, output in testcases:
        print(f"{inorder=}")
        print(f"{postorder=}")
        result = reconstruct_tree(
            inorder,
            postorder
        )
        print(f"{result=}")
        print(f"{output=}")
        assert result == output


if __name__ == "__main__":
    main()
