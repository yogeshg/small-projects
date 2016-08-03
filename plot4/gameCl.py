import sys
import traceback
# from threading import *

from game import *

class GameAi:
    def __init__( self, game, player, other ):
        self.reinit(game, player, other)

    def reinit(self, game, player, other):
        self.game = game
        self.player = player
        self.other = other
        self.move=Move(0,0)
        self.anticipatedMove = Move(0,1)
        return

    def startCalc( self ):
        for d in range(6):
            try:
                stats.register('cache_eval')
                stats.register('force_eval')
                stats.register('cache_size')
                self.game._statskey_cached='cache_eval'
                self.game._statskey_forced='force_eval'

                result = getAlphaBeta( self.game, self.player, self.other, reward=AlphaBeta(-4,4), depth=d )
                print 'Optimal move and reward at depth {} - {}'.format(d, result)
                self.move = result.move
            except (KeyboardInterrupt):
                break
            finally:
                stats.collect('cache_size', len(self.game._cache))
                stats.show()
        # in a new thread,
        # update self.move
        return

    def interruptCalc( self ):
        # stop that thread
        return

    def getMove( self, interval=10 ):
        self.startCalc()
        # sleep( interval )
        # self.interruptCalc()
        return self.move

class GameCl:
    def __init__( self, n ):
        self.game = Game(n)
        self._PLAYERS = { 1:'X', 2:'O'}
        self._ROWS = '0123456789'+80*'.'
        self._COLS = self._ROWS
        self._AI = { 1:GameAi(self.game,1,2), 2:GameAi(self.game,2,1) }
        self.level = 10
        return

    def getMoveAi( self, player, other ):
        self._AI[player].reinit(self.game, player, other)
        move = self._AI[player].getMove( interval=self.level )
        return move


    def getMoveCl( self, player ):
        movetxt = sys.stdin.readline()
        move = None
        while not move :
            try :
                move = Move(*[int(x) for x in movetxt.split(',')])
            except :
                print 'Unable to parse, please enter move as: row,col ...'
                movetxt = sys.stdin.readline()
        return move

    def show( self ):

        for r in reversed(self.game.ROWS):
            print self._ROWS[r],'|',
            for c in self.game.COLS:
                print self._PLAYERS.get( self.game.board[r,c] , ' ' ),
            print

        print '-','+',
        for c in self.game.COLS:
            print '-',
        print

        print ' ','|',
        for c in self.game.COLS:
            print self._COLS[c],
        print
        return

    def judge(self):
        if( 4<=self.game.evaluate(1)) :
            return 1
        elif (4<=self.game.evaluate(2)) :
            return 2
        else:
            return 0

    def play( self, player1=True, player2=True ):
        '''
        player1/player2: True if command line, False if Ai
        '''
        while( not self.judge() ):

            player1Moved = False
            player2Moved = False

            self.show()
            print 'Player 1 move...'
            if( player1 ):
                move = self.getMoveCl(1)
            else :
                move = self.getMoveAi(1, 2)
            player1Moved = self.game.move(1, move)
            if(not player1Moved):
                print 'Invalid move, chance skipped'

            self.show()
            print 'Player 2 move...'
            if( player2 ):
                move = self.getMoveCl(2)
            else :
                move = self.getMoveAi(2, 1)            
            player2Moved = self.game.move(2, move)
            if(not player2Moved):
                print 'Invalid move, chance skipped'

        self.show()
        print "Player", self.judge(), "won!!!"

