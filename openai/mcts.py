# import standard python modules
import sys
import random
import time
import itertools
from copy import copy

# import third party modules
import gym

# import own modules
from plot4 import stats

# taken from https://gym.openai.com/evaluations/eval_9ZnTspgvSYK6O0PCkEFYQ
def combinations(space):
    if isinstance(space, gym.spaces.Discrete):
        return xrange(space.n)
    elif isinstance(space, gym.spaces.Tuple):
        return itertools.product(*[combinations(s) for s in space.spaces])
    else:
        raise NotImplementedError


class GameTree():
    '''
    This is the tree where we will run MCTS
    '''
    def __init__(self, parent, state):
        self.parent = parent
        self.state = state
        self.child_paths = (list(combinations(state.action_space)))
        self.num_child_paths = len(self.child_paths)
        # self.child_paths_done = 0
        self.children = [None]*self.num_child_paths

        self.best_reward = float('-inf') # find out the max reward of this state
        self.best_action = None

        self.rewards = stats.Stat('x')

        self.obv = None
        self.reward = 0
        self.done = False

    def explore(self, reward_so_far=0, lambda_factor=0.9):
        '''
        This function explores a random path from the tree
        '''
        reward_so_far = reward_so_far+lambda_factor*self.reward
        if(self.done):
            # print 'return', self.reward
            return_val = reward_so_far
        else:
            x = random.randrange(0,self.num_child_paths)
            action = self.child_paths[x]
            # print action,
            if( None == self.children[x] ):
                state = copy(self.state)
                obv, reward, done, _ = state.step(action)
                # print obv, reward, done,
                self.children[x] = GameTree(self, state)
                self.children[x].obv = obv
                self.children[x].reward = reward
                self.children[x].done = done
                self.children[x].rewards = stats.Stat(self.rewards.name+'->'+str(action))
            # print '>',
            return_val = self.children[x].explore(reward_so_far=reward_so_far
                )
        self.rewards.collect(return_val)
        return return_val

class MctsAi():

    def __init__(self, env, NUM_ITER=10000):
        self.NUM_ITER = NUM_ITER
        self.root = GameTree( None, copy(env) )
        del self.root.state._monitor
        self.env = env
        self.obv = None
        self.rew = None
        self.done = False
        self.info = None
        self.act = None
        return

    def play(self):
        for _ in xrange(self.NUM_ITER):
            self.root.explore()
        func = lambda pair: (pair[1].rewards.max,pair[1].rewards.avg) if pair[1] else float('-inf')
        node = self.root
        # print 'Playing best actions seen so far'
        num_loop = 0
        while( node ):
            (i,_) = max(list(enumerate(node.children)), key=func)
            if(not num_loop):
                # print node.rewards
                for c in node.children:
                    if c:
                        1
                        # print c.rewards
                self.act = node.child_paths[i]
                # print self.act,
                self.obv, self.rew, self.done, self.info = self.env.step(self.act)
                # print self.obv, self.rew, self.done, self.info
                # self.env.render()
                self.root = node.children[i]
                # print 'Strategy as of now:',
            # print node.child_paths[i],'>',
            node = node.children[i]
            num_loop += 1
        # print

    def playAll(self):
        while(not self.done):
            self.play()

def main():
    try:
        NUM_ITER=int(sys.argv[1])
    except:
        NUM_ITER=1000
    try:
        NUM_EPISODES=int(sys.argv[2])
    except:
        NUM_EPISODES=1
    try:
        UPLOAD = bool(sys.argv[3])
    except:
        UPLOAD = False
    try:
        PROBLEM = sys.argv[4]
    except:
        PROBLEM = 'Copy-v0'
    DIR = '/tmp/openai/'+PROBLEM+'/'

    env = gym.make(PROBLEM)
    env.monitor.start(DIR, force=True)
    for _ in xrange(NUM_EPISODES):
        print 'running episode', _
        env.reset()
        ai = MctsAi(env, NUM_ITER=NUM_ITER)
        ai.playAll()
    env.monitor.close()

    if(UPLOAD):
        gym.upload(DIR, api_key='sk_xzHs5ZzjQviZDZ8R2luFPw')

    return 0

if __name__ == '__main__':
    main()
