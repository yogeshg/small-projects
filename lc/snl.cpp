#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

class Game {
    public:
        Game() {
            for(int i=0; i<100; ++i) {
                squares[i]=-1;
            }
        }
        void readFromCin() {
            int ladders, snakes, t1, t2;
            cin >> ladders;
            for(int i=0;i<ladders;++i) {
                cin >> t1 >> t2;
                assert(t1 < t2);
                addlink(t1, t2);
            }
            cin >> snakes;
            for(int i=0;i<snakes;++i) {
                cin >> t1 >> t2;
                assert(t1 > t2);
                addlink(t1, t2);
            }
            return;
        }
        void addlink(int t1, int t2) {
            squares[t2] = t1;   // t2 is accessible from t1
        }
        typedef pair<int,int> p;
        int minTurns() {
            //int turns = 0;
            //int idx = 99;
            vector<p> stack;
            stack.push_back(p(99,0));
            int best_turns = 99;
            while( stack.size() ) {
                const int currentSqr = stack.back().first;
                const int currentTurns = stack.back().second;
                if(currentTurns >= best_turns) {
                    cout << "\n";
                    stack.pop_back();
                } else {
                    cout << currentSqr<<","<<currentTurns<< " ";
                    if(currentSqr<=0) {
                        if(currentSqr==0) {
                            best_turns = std::min(best_turns, currentTurns);
                            cout << "\n";
                        }
                        stack.pop_back();
                    } else {
                        const int ladderFrom = squares[currentSqr];
                        stack.pop_back();
                        for(int dice=1; dice<=std::min(6,currentSqr);++dice) {
                            stack.push_back( p(currentSqr-dice, currentTurns+1) );
                        }
                        if((0<ladderFrom) && (currentSqr>ladderFrom )) {
                            stack.push_back( p(ladderFrom, currentTurns) );
                        }
                    }
                }
            }
            return best_turns;
        }
    
    private:
        int squares[100];
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int ngames;
    cin >> ngames;
    for(int i=0; i<ngames; ++i) {
        Game g;
        g.readFromCin();
        cout << g.minTurns() <<"\n";
    }
    return 0;
}

