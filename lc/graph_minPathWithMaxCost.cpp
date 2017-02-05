#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <climits>
#include <queue>
using namespace std;

struct Edge {
    int st;
    int end;
    int cost;
    // Edge() : st(0), end(0), cost(0) {};
    Edge(const int& s, const int& e, const int& c) : st(s), end(e), cost(c) {};
    // Edge(const Edge& e) : st(e.st), end(e.end), cost(e.cost) {}
    string toString() const{
        stringstream ss;
        ss << "(" << st << "->" << end <<" : " << cost << ")";
        return ss.str();
    }
};

typedef vector<Edge> EdgeSet;

class Graph {
    public:
    
    Graph(int n) : N(n) {}

    void addEdge(Edge& e) {
        edges[e.st].push_back(e);
    }
    
    void addBiEdge(int st, int end, int cost) {
        Edge e1(st, end, cost);
        Edge e2(end, st, cost);
        addEdge(e1);
        addEdge(e2);
    }
    
    string toString() {
        stringstream ss;
        for(int vertex=1; vertex<=N; vertex++) {
            ss << vertex << ":";
            for(auto e: edges[vertex]) {
                ss << e.toString() <<",";
            }
            ss <<"\n";
        }
        return ss.str();
    }
    
    // private:
    const int N;
    unordered_map<int,EdgeSet> edges;

};

int minPathWithMaxCost(Graph& g) {
    unordered_map<int, bool> visited;
    queue<int> queue;
    int cost[g.N+1];
    for(int i=0; i<g.N; ++i) {
        cost[i]=INT_MAX;
    }
    cost[g.N]=0;
    queue.push(g.N);
    while(queue.size()) {
        const int v = queue.front();
        queue.pop();
        if(!visited[v]) {
            visited[v] = true;
            cerr << "visiting:"<<v;
            for( auto& e: g.edges[v] ) {
                cerr << " e:"<<e.toString();
                if(visited[e.end]) {
                    // int c = ;
                    cost[v] = std::min(cost[v], std::max(cost[e.end], e.cost));
                } else {
                    queue.push(e.end);
                }
            }
            cerr<<" out\n\t";
            for(int i=0; i<=g.N; ++i) {
                cerr << cost[i] << " ";
            }
            cerr<<"\n";
        }
    }
    
    
    return cost[1];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, E, s, e, c;
    cin >> N >> E;
    Graph g(N);
    for(int i=0; i<N; ++i) {
        cin >> s >> e >> c;
        g.addBiEdge(s,e,c);
        // std::cout << g.toString() << "\n";
    }
    cout << minPathWithMaxCost(g);
    return 0;
}

