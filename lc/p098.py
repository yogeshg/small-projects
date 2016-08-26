# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

def inOrderTraversal(root, max_so_far):
    left_child = root.left
    right_child = root.right
    if( left_child ):
        max_so_far = inOrderTraversal(left_child, max_so_far)
    assert(max_so_far < root.val)
    max_so_far = root.val
    if( right_child ):
        max_so_far = inOrderTraversal(right_child, max_so_far)
    return max_so_far

class Solution(object):
    def isValidBST(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """
        if(root):
            try:
                inOrderTraversal(root,float('-inf'))
            except (AssertionError):
                return False
        return True

