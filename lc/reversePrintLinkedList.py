class LinkedList():
    def __init__(self, val, next):
        self.val = val
        self.next = next
        return


def prepend(ll, val):
    return LinkedList(val, ll)

def append(llast, val):
    assert llast.next is None, 'append to the last element only!'
    llast.next = LinkedList(val, None)
    return


def reversePrintLinkedList(ll, length):    # print 0 to n
    if( length > 1):
        mid = length/2
        mid_point = ll
        for i in range(mid):
            mid_point = mid_point.next
        reversePrintLinkedList(mid_point, length-mid)   # print [n/2]+1, n
        reversePrintLinkedList(ll, length/2)            # print 0 to [n/2]
    else :
        print ll.val
    return


ll = None
ll = prepend(ll, 1)
ll = prepend(ll, 2)
ll = prepend(ll, 3)
ll = prepend(ll, 4)
ll = prepend(ll, 5)
ll = prepend(ll, 6)

reversePrintLinkedList(ll, 6)
