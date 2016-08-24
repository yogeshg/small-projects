import logging
logging.basicConfig(level=logging.INFO)

def getAnswer(leftSearch, rightSearch):
    # logging.debug('\tgetAnswer %d %d', leftSearch, rightSearch)
    if( leftSearch<0 ):
        if( rightSearch<0):
            return -1
        else: # rightSearch successful
            return rightSearch
    else: # leftSearch successful
        return leftSearch


class Solution(object):

    def bsearch(self, nums, target, start, end):
        """
        This is the simple binary search
        """
        logging.debug('bsearch %d %d', start, end)
        if( end<=start ):
            if (target==nums[start]):
                # logging.debug('\tbasecase %d', start)
                return start
            else:
                # logging.debug('\tbasecase %d', -1)
                return -1
        else: # end > start
            mid = int((start+end)/2) # mid might be == start, mid < end, mid+1 might be == end
            leftSearch = self.bsearch(nums, target, start, mid)
            rightSearch = self.bsearch(nums, target, mid+1, end)
            return getAnswer(leftSearch, rightSearch)

    def rbsearch(self, nums, target, start, end):
        """
        This is the binary search in a rotated array
        """
        logging.debug('rbsearch %d %d', start, end)
        if( end<=start ):
            return self.bsearch( nums, target, start, end )
        else:
            mid = int((start+end)/2) # mid might be == start, mid < end, mid+1 might be == end
            if(nums[mid] >= nums[start]):
                leftSearch = self.bsearch(nums, target, start, mid)
            else:
                leftSearch = self.rbsearch(nums, target, start, mid)
            if(nums[end] >= nums[mid+1]):
                rightSearch = self.bsearch(nums, target, mid+1, end)
            else:
                rightSearch = self.rbsearch(nums, target, mid+1, end)
            return getAnswer(leftSearch, rightSearch)
            

    def search(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        logging.info('search %s %d', str(nums), target)
        return self.rbsearch(nums, target, 0, len(nums)-1)
        
if __name__ == '__main__':
    s = Solution()
    for x in range(14):
        print s.search([9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8], x)

