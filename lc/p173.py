class BSTIterator(object):
    def __init__(self, root):
        self.stack = []                         # stack is a root,state tuple
        self.len_stack = 0
        while(root):
            self.len_stack+=1
            self.stack.append(root)
            root = root.left

    def hasNext(self):
        return self.len_stack

    def next(self):
        self.len_stack-=1
        item = self.stack.pop()
        root = item.right
        while(root):
            self.len_stack+=1
            self.stack.append(root)
            root = root.left
        return item.val
