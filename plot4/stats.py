'''
This is a simple stat collector module.

    show()
    register('s1')
    collect('s1',1)
    collect('s1',2)
    collect('s1',3)
    collect('s1',1)
    collect('s1',7)
    show()
    try:
        collect('s2',7)
    except KeyError as e:
        assert e.args[0] == 's2'
        
    #   name      :      count                  min                  avg                  max
    #   name      :      count                  min                  avg                  max
    #   s1        :          5         7.0000000000         2.8000000000         7.0000000000

'''
class Stat():
    def __init__(self, name):
        '''
        This class is used to store statistics of a particular type

            s1 = stats.Stat('s1')
            s1.collect(0.01)
            s1.collect(3.14)
            s1.collect(0.25)
            print s1
            
            #   s1        :          3         0.2500000000         1.1333333333         3.1400000000
        '''
        self.name = name
        self.max = 0
        self.min = 0
        self.count = 0
        self.avg = 0

    def collect(self, val):
        n = self.count
        den = (1.0/(n+1))
        self.count += 1
        self.max = max(self.max, val)
        self.min = min(self.max, val)
        self.avg = (n*den*self.avg) + (den*val)

    def __str__(self):
        return "{0:10}: {1:10d} {2:20.10f} {3:20.10f} {4:20.10f}".format(self.name, self.count, self.min, self.avg, self.max)

allStats = {}

def register(key):
    allStats[key] = Stat(key)

def collect(key,value):
    allStats[key].collect(value)

def show():
    print "{0:10}: {1:>10} {2:>20} {3:>20} {4:>20}".format('name','count','min','avg','max')
    for s in allStats.itervalues():
        print s

def main():
    show()
    register('s1')
    collect('s1',1)
    collect('s1',2)
    collect('s1',3)
    collect('s1',1)
    collect('s1',7)
    show()
    try:
        collect('s2',7)
    except KeyError as e:
        assert e.args[0] == 's2'

if __name__ == '__main__':
    main()
