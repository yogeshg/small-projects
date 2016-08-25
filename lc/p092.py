# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

# def node2str(node):
#     try:
#         return 'Node('+str(node.val)+','+str(type(node.next))+')'
#     except:
#         return 'Node(Null)'
        
def getNthNode(head, prev, count=1):
    if(count>1):
        return getNthNode(head.next, head, count-1)
    else:
        # print 'returning', node2str(head), node2str(prev)
        return (head, prev)

def revLl(head, list_so_far, to_flip):
    next_head = head.next
    head.next = list_so_far
    if( next_head and to_flip ):
        return revLl(next_head, head, to_flip-1)
    else:
        return (head, next_head)

class Solution(object):
    def reverseBetween(self, head, m, n):
        """
        :type head: ListNode
        :type m: int
        :type n: int
        :rtype: ListNode
        """
        part1_head = head
        (part2_head, part1_tail) = getNthNode(head, None, m)
        part2_head_new,part3_head = revLl(part2_head, None, n-m)
        part2_head.next = part3_head
        if(part1_tail):
            part1_tail.next = part2_head_new
            return part1_head
        else:
            return part2_head_new

