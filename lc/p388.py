import logging
logging.basicConfig(level=logging.DEBUG)

def extendArr(arr, n):
    if( len(arr) < n ): # needs to be extended
        arr.extend([0]*(n-len(arr)))
    return

def unextendArr(arr, n):
    while(len(arr) > n):
        arr.pop()
    return

class Solution(object):

    def __init__(self):
        self.logger = logging.getLogger(__name__)
        self.input = ""
        self.length = 0
        self.last_level = 0
        self.lengths = []
        self.max_length_so_far = 0
        return

    def countChars(self, index):
        num = 0
        isFile = 0
        while((index<self.length) and (self.input[index]!='\n')):
            if (self.input[index]=='.'):
                isFile+=1
            index+=1
            num += 1
        return (num, isFile)
    
    def countTabs(self, index):
        num = 0
        while((index<self.length) and (self.input[index]=='\t')):
            index+=1
            num += 1
        return num
    
    def processLine(self, index):
        while((index < self.length) and (self.input[index]!='\n')):
            num_tabs = self.countTabs(index)
            index += num_tabs
            self.logger.debug('num_tabs %d %d', num_tabs, index)
            (num_chars, isFile) = self.countChars(index)
            index += num_chars
            self.logger.debug('num_chars %d %d', num_chars, index)
        extendArr(self.lengths, num_tabs+1)
        unextendArr(self.lengths, num_tabs+1)
        self.lengths[num_tabs] = num_chars
        length_line = sum(self.lengths) + num_tabs
        self.last_level = num_tabs
        index+=1
        if(isFile):
            self.max_length_so_far = max(self.max_length_so_far, length_line)
        self.logger.debug('line seen')
        self.logger.info('length_line %d', length_line)
        self.logger.info('num_tabs %d', num_tabs)
        return index
    
    def lengthLongestPath(self, input):
        """
        :type input: str
        :rtype: int
        """
        self.logger.info(input)
        self.input = input
        self.length = len(input)
        index = 0
        while(index<self.length):
            index = self.processLine(index)
        return self.max_length_so_far

if __name__ == '__main__':
    s = Solution()
    a = s.lengthLongestPath('dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext\n\toogaboobaooo.txt')
    s.logger.warn('answer %d', a)
