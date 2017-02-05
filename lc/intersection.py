


def intersectSorted(l1, l2):
    i = 0
    j = 0
    r = []
    while(i<len(l1) and j<len(l2)):

        if( l1[i] < l2[j] ):
            i+=1
        elif( l1[i] > l2[j] ):
            j+=1
        else:
            r.append(l1[i])
            i+=1
            j+=1
    return r

a = [11, 12, 13, 21, 22, 23, 24, 25, 31, 32, 33, 41]
b = [11, 12, 13, 14, 15, 23, 24, 25, 31, 32, 33, 42]


print intersectSorted(a,b)
