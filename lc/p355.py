
def ensureKeyHasSelfSet(dic, key):
    if( not dic.has_key(key) ):
        dic[key] = set()
        dic[key].add(key)
    # else: dic has key, whatever it has
    return

# def ensureKeyHasList(dic, key):
#     if( not dic.has_key(key) ):
#         dic[key] = []
#     # else: dic has key, whatever it has
#     return

# def ensureKeyHasNum(dic, key):
#     if( not dic.has_key(key) ):
#         dic[key] = 0
#     # else: dic has key, whatever it has
#     return

class Twitter(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        # list of (user, tweet)
        # self.tweetLists = {}
        # self.tweetLens = {}
        self.allTweets = []
        self.lenTweets = 0
        self.followSets = {}

    def postTweet(self, userId, tweetId):
        """
        Compose a new tweet.
        :type userId: int
        :type tweetId: int
        :rtype: void
        """
        # ensureKeyHasList( self.tweetLists, userId )
        # ensureKeyHasNum( self.tweetLens, userId )
        # self.tweetLists[userId].append(tweetId)
        self.allTweets.append( (userId, tweetId) )
        self.lenTweets += 1
        return

    def getNewsFeed(self, userId):
        """
        Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.
        :type userId: int
        :rtype: List[int]
        """
        count = 10
        feed = []
        ensureKeyHasSelfSet(self.followSets, userId)
        followSet = self.followSets[userId]
        for i in range( self.lenTweets-1, -1, -1):
            if( count ):
                (userId, tweetId) = self.allTweets[i]
                if userId in followSet:
                    count-=1
                    feed.append(tweetId)
            else:
                break
        return feed

    def follow(self, followerId, followeeId):
        """
        Follower follows a followee. If the operation is invalid, it should be a no-op.
        :type followerId: int
        :type followeeId: int
        :rtype: void
        """
        ensureKeyHasSelfSet(self.followSets, followerId)
        self.followSets[followerId].add(followeeId)
        return

    def unfollow(self, followerId, followeeId):
        """
        Follower unfollows a followee. If the operation is invalid, it should be a no-op.
        :type followerId: int
        :type followeeId: int
        :rtype: void
        """
        ensureKeyHasSelfSet(self.followSets, followerId)
        checks = True
        checks = checks and (followerId!=followeeId)
        checks = checks and (followeeId in self.followSets[followerId])
        if( checks ):
            self.followSets[followerId].remove(followeeId)
        return

# Your Twitter object will be instantiated and called as such:
# obj = Twitter()
# obj.postTweet(userId,tweetId)
# param_2 = obj.getNewsFeed(userId)
# obj.follow(followerId,followeeId)
# obj.unfollow(followerId,followeeId)
