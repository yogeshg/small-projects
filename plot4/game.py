# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <codecell>

import numpy as np
import random
random.seed()

from Queue import PriorityQueue
import copy


# <codecell>

class Move(object):
    def __init__(self, row, col) :
        self.row = row
        self.col = col
    def __str__(self):
        return str((self.row,self.col))

class AlphaBeta():
    def __init__( self, a, b, e=0):
        self.alpha = a
        self.beta = b
        self.evaluation = e
        self._random = random.random()
        
    def __str__(self):
        return str((self.alpha,self.beta,self.evaluation))
        
    def __cmp__(self, other):
#         print self, other, 
        c1 = cmp(self.alpha,other.alpha)
        if( c1!=0 ):
#             print c1
            return -c1
        else:
            c2 = cmp(self.beta,other.beta)
            if( c2!=0 ):
#                 print c1, c2
                return -c2
            else:
                c3 = cmp(self.evaluation,other.evaluation)
                if( c3!=0 ):
#                     print c1, c2, c3
                    return -c3
                else:
                    c4 = cmp(self._random,other._random)
#                     print c1, c2, c3, c4
                    return c4

class AlphaBetaOfMove():
    def __init__( self, abe, mv ):
        self.alphabeta = abe
        self.move = mv
        
    def __str__(self):
        return str(self.move) + ":" + str(self.alphabeta)
        
    def __cmp__( self, other ):
        return cmp(self.alphabeta, other.alphabeta)

# <codecell>

# TEST of Moves and Classes

# from Queue import PriorityQueue
# q = PriorityQueue()
# q.put( AlphaBetaOfMove( AlphaBeta( -5, 5, 1), Move(1, 1) ) )
# q.put( AlphaBetaOfMove( AlphaBeta( -5, 5, 2), Move(2, 2) ) )
# q.put( AlphaBetaOfMove( AlphaBeta( -4, 5 ), Move(3, 3) ) )
# q.put( AlphaBetaOfMove( AlphaBeta( -4, 5 ), Move(4, 4) ) )
# q.put( AlphaBetaOfMove( AlphaBeta( -4, 4 ), Move(5, 5) ) )
# q.put( AlphaBetaOfMove( AlphaBeta( 5, 5 ), Move(6, 6) ) )
# q.put( AlphaBetaOfMove( AlphaBeta( -5, -5 ), Move(7, 7) ) )

# print q.get()
# print q.get()
# print q.get()
# print q.get()
# print q.get()
# print q.get()
# print q.get()

# <codecell>

def max_continuous( l, a ):
    result_so_far = 0
    seen_so_far = 0
    for val in l:
        if( val == a ):
            seen_so_far = seen_so_far+1
            result_so_far = max(result_so_far,seen_so_far)
        else: # val!=a
            seen_so_far = 0
#         print (val,seen_so_far, result_so_far),
#     print result_so_far
    return result_so_far

# <codecell>

class Game(object):
    
    # game is self
    def __init__(game, n):
        game.n = n
        game.COLS = range(game.n);
        game.ROWS = range(game.n);
        game.DIAG = range(1-game.n,game.n);
        game.TARGET = 4
        game.board = np.matrix( [[0 for col in game.COLS] for row in game.ROWS] )
    
    def is_move_valid( game, row, col ):
        return (row<game.n) and (col<game.n) and game.board[row,col]==0

    def next_moves( game ):
        for col in game.COLS:
            maxrow = -1
            for row in game.ROWS:
                if( game.board[row,col] != 0 ):
                    maxrow = row
            if( game.is_move_valid( maxrow+1, col ) ):
                yield Move(maxrow+1, col)
        return
    
    def DIAG1( game, k ):
        for r in range(-game.n,game.n):
            c = k+r
            if( (r>=0) and (r<game.n) and (c>=0) and (c<game.n) ):
                yield Move(r,c)
                    
    def DIAG2( game, k1 ):
        k = game.n + k1
        for r in range(-game.n,game.n):
            c = k-r
            if( (r>=0) and (r<game.n) and (c>=0) and (c<game.n) ):
                yield Move(r,c)
                
    def move( game, player, m ):
        if( game.is_move_valid(m.row, m.col) ):
            game.board[m.row,m.col] = player
            return True
        else:
            return False
        
    def evaluate( game, player ):
    
        result_row = 0
        for r in game.ROWS:
            r = max_continuous( [game.board[r,c] for c in game.COLS], player )
            result_row = max( result_row, r )
    #     print result_row
    
        result_col = 0
        for c in game.COLS:
            r = max_continuous( [game.board[r,c] for r in game.ROWS], player )
            result_col = max( result_col, r )
    #     print result_col
    
        result_d1 = 0
        for d1 in game.DIAG:
            r = max_continuous( [game.board[m.row,m.col] for m in game.DIAG1(d1)], player )
            result_d1 = max( result_d1, r )
    #     print result_d1
    
        result_d2 = 0
        for d2 in game.DIAG:
            r = max_continuous( [game.board[m.row,m.col] for m in game.DIAG2(d2)], player )
            result_d2 = max( result_d2, r )
    #     print result_d2
        return max( result_row,  result_col, result_d1, result_d2 )


# <codecell>

# returns maximum score for player, assuming other minimises for player (== maximises for other)
def getAlphaBeta( game, player, other, reward=AlphaBeta(-100,100), depth=10, tab=0 ):
    '''
    alpha: minimum bound of the outcome -- currently, evaluate of best move possible by other
    beta: maximum bound of the outcome -- currently, evaluate of best move possible by player
    
    returns: (alpha, beta, evaluation, move)
    '''
    # evaluation is the current value of board, assuming no more moves in future
    # alpha == beta == finalvalue if we figure out the outcome.
    reward.evaluation = game.evaluate( player )
    move = Move(-1,-1)
    # base case: can't play further, lost
    if (reward.evaluation==reward.beta):
#         print 'Player', player, 'won!!!'
        return AlphaBetaOfMove(AlphaBeta(reward.beta, reward.beta, reward.beta), move)
    # base case: can't evaluate further
    if (depth == 0):
        return AlphaBetaOfMove(reward, move )
    q = PriorityQueue()
    for m in game.next_moves( ):
            g2 = copy.deepcopy( game )
            g2.move( player, m)
#             a = evaluate( g2, player ) TODO: check if we won
#             if a > alpha :
#                 a_so_far = a
#                 (a_r, a_c) = ( row, col )
#                 if a == TARGET:
#                     return ( a, row, col )
            #(other_alpha, other_beta, other_evaluation, other_r, other_c) = 
            oponent_reward = AlphaBeta(-reward.beta, -reward.alpha, -reward.evaluation)
            oponent_reward = getAlphaBeta(g2, other, player, reward=oponent_reward, depth=depth-1, tab=tab+1 ).alphabeta
            player_reward = AlphaBeta(-oponent_reward.beta, -oponent_reward.alpha, -oponent_reward.evaluation)
            q.put_nowait( AlphaBetaOfMove( player_reward, m ) )
#             if( tab < 1 ):
#                 print ("\t"*tab), (player,row,col), (other,other_r,other_c), (other_alpha,other_beta,other_evaluation), (next_alpha,next_beta,evaluation), update
    if( q.empty() ):
        return AlphaBetaOfMove( reward, Move(-1,-1) )
    else:
        return q.get_nowait()


