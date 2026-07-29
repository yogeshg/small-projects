from collections import deque

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# def level_order(root):
#     if not root:
#         return []
    
#     result = []
#     queue = deque([root])

#     while queue:
#         level_size = len(queue)
#         current_level = []

#         for _ in range(level_size):
#             node = queue.popleft()
#             current_level.append(node.val)

#             if node.left:
#                 queue.append(node.left)
#             if node.right:
#                 queue.append(node.right)

#         result.append(current_level)

#     return result


def level_order(root):
    if not root:
        return []
    result = []
    queue = deque()
    queue.append(root)

    while queue:
        node = queue.popleft()
        result.append(node.val)
        if node.left:
            queue.append(node.left)
        if node.right:
            queue.append(node.right)
    return result


def test():
    #       1
    #      / \
    #     2   3
    #    / \   \
    #   4   5   6

    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.left = TreeNode(4)
    root.left.right = TreeNode(5)
    root.right.right = TreeNode(6)

    print(level_order(root))
    # Output: [[1], [2, 3], [4, 5, 6]]



def test2():
    #       1
    #      / \
    #     2   3
    #        / \
    #       5   6

    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.right.left = TreeNode(5)
    root.right.right = TreeNode(6)

    print(level_order(root))
    # Output: [[1], [2, 3], [5, 6]]


def main():
    return test()


if __name__ == "__main__":
    main()
