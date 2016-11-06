# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

def kthIot(root, to_see):
    left_child = root.left
    right_child = root.right
    if( left_child ):
        (nodeval, to_see) = kthIot(left_child, to_see)
        if( to_see==0 ):
            return (nodeval, 0)
    to_see -= 1
    if( to_see==0 ):
        return (root.val, 0)
    if( right_child ):
        (nodeval, to_see) = kthIot(right_child, to_see)
        if( to_see==0 ):
            return (nodeval, 0)
    return( None, to_see )

class Solution(object):
    def kthSmallest(self, root, k):
        """
        :type root: TreeNode
        :type k: int
        :rtype: int
        """
        (val, _) = kthIot(root, k)
        return val

