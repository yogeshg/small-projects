
import matplotlib.pyplot as plt
import matplotlib.widgets as mwidgets
from game import *
# <codecell>

class GameGui:
    
    def __init__( self, game ):
        self.game = game
        self.turn = 0
        self.x = -1
        self.y = -1
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(1,1,1)
        self.imgplot = None

    def paint(self):
        if( self.ax ):
            self.ax.clear()
        if( self.fig ):
            self.fig.clf()
        plt.close()
        self.fig = plt.figure()
        self.ax = self.fig.add_subplot(1,1,1)
        
        self.imgplot = self.ax.imshow( self.game.board.tolist(), interpolation='none' )
        
        self.cursor = mwidgets.Cursor(self.ax, useblit=True, color='k')
        self.cursor.horizOn = False

        self.connect = self.ax.figure.canvas.mpl_connect
        self.disconnect = self.ax.figure.canvas.mpl_disconnect

        self.clickCid = self.connect("button_press_event",self.onClick)

        plt.show()

    def judge(self):
        if( 4<=self.game.evaluate(1)) :
            return 1
        elif (4<=self.game.evaluate(2)) :
            return 2
        else:
            return 0

    def getAutoMove( self, player, other ):
        print "getAutoMove", player, other
        for d in range(6):
            try:
                result = getAlphaBeta( self.game, player, other, reward=AlphaBeta(-4,4), depth=d )
                print result
            except:
                break
        self.game.move( player, result.move )
        print self.game.board
    
    def play( self, player1=1, player2=2 ):
        while( not self.judge() ):

            if( player1 ):
                self.getMove( player1 )
            else :
                self.getAutoMove( 1,2 )

            if( player2 ):
                self.getMove( player2 )
            else :
                self.getAutoMove( 2,1 )

        print "Player", self.judge(), "won!!!"
    
    
    def getMove( self, player ):
        print "Move of player", player, 
        self.paint() # Blocking
        m = Move( int(self.y+0.5), int(self.x+0.5) )
        print 'moving', player, str(m)
        self.game.move( player, m )


    def onClick(self, event):
        if event.inaxes:
            self.x = event.xdata
            self.y = event.ydata
            print "clicked", self.x, self.y
            self.cleanup()

    def cleanup(self):
        self.disconnect(self.clickCid)
        # plt.clf()
        plt.close()
        print 1

# <codecell>

