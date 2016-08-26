# Definition for a  binary tree node
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

# import sys, logging
# logging.basicConfig(stream=sys.stdout, level=logging.DEBUG)

def pushTillFirst(root, stack):
    if( root ):
        # logging.debug('pushing %d', root.val)
        stack.append(root)
        return pushTillFirst(root.left, stack)
    return

class BSTIterator(object):
    def __init__(self, root):
        """
        :type root: TreeNode
        """
        logging.info('initing')
        self.stack = []                         # stack is a root,state tuple
        pushTillFirst(root, self.stack)

    def hasNext(self):
        """
        :rtype: bool
        """
        logging.info('hasNext %s', len(self.stack))
        return len(self.stack)

    def next(self):
        """
        :rtype: int
        """
        logging.info('next')
        item = self.stack.pop()
        pushTillFirst(item.right, stack)
        return item.val


# Your BSTIterator will be called like this:
# i, v = BSTIterator(root), []
# while i.hasNext(): v.append(i.next())