def resetLastSeen(ls, x):
    for i in range(len(ls)):
        if( ls[i] <= x ):
            ls[i] = -1

def indexLastSeen(c):
    return ord(c)

class Solution(object):
    
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        N = len(s)
        longestSoFar = 0
        longestEndingHere = [1] * N
        alphabetLastSeen = [-1]*65536
        if(N>0):
            longestSoFar = 1
            alphabetLastSeen[indexLastSeen(s[0])] = 0
        
        for i in range(1,N):
            c = indexLastSeen(s[i])
            j = alphabetLastSeen[c]
            if (j < 0):
                longestEndingHere[i] = longestEndingHere[i-1]+1
            else:
                resetLastSeen(alphabetLastSeen, j)
                longestEndingHere[i] = i-j
            alphabetLastSeen[c] = i
            longestSoFar = max(longestSoFar, longestEndingHere[i])
        print longestEndingHere
        return longestSoFar

