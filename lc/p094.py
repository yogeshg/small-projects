# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

# l = []

# def recIot(root):
#     if(root.left):
#         recIot(root.left)
#     l.append(root.val)
#     if(root.right):
#         recIot(root.right)
#     return

def ittIot(root):
    stack = []
    list = []
    stack.append((root,0))
    while(len(stack)):
        # print stack
        (item,state) = stack.pop()
        if( state == 0 ):
            # print item.val                  ## For PreOrderTraversal
            stack.append((item,1))
            if( item.left ):
                stack.append((item.left,0))
        if( state == 1 ):
            # print item.val                  ## For InOrderTraversal
            list.append(item.val)
            stack.append((item,2))
            if( item.right ):
                stack.append((item.right,0))
        # if( state == 2 ):
        #     # print item.val                  ## For PostOrderTraversal
        #     pass

    return list

class Solution(object):
    def inorderTraversal(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        if(root):
            return ittIot(root)
        else:
            return []
