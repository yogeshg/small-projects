#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<sstream>
#include<string>
#include<utility>
#include<vector>
#include<iostream>
#include<algorithm>
#include<set>
#include<stack>

template<typename Representation>
concept bool Graph = requires(Representation r, typename Representation::Vertex_ptr x, typename Representation::Edge_ptr e) {
    typename Representation::Vertex_ptr;
    typename Representation::Edge_ptr;
    {r.add_vertex(x)}->void;
    {r.vertices()} -> std::vector<typename Representation::Vertex_ptr>;
    {r.adjacent(x, x)} -> bool;
    {r.add_edge(e)} -> void;
    {r.edges()} -> std::vector<typename Representation::Edge_ptr>;
    {r.edges_from(x)} -> std::vector<typename Representation::Edge_ptr>;
    {r.top()} -> typename Representation::Vertex_ptr;
    {e} -> bool;
    {e->start} -> typename Representation::Vertex_ptr;
    {e->end} -> typename Representation::Vertex_ptr;
    {make_edge(x,x)} -> typename Representation::Edge_ptr;
    {r.num_vertices()} -> int;
    {r.num_edges()} -> int;
};

template<Graph Representation>
bool adjacent(Representation& g, typename Representation::Vertex_ptr x, typename Representation::Vertex_ptr y) {
    return g.adjacent(x, y);
}
template<Graph Representation>
std::vector<typename Representation::Vertex_ptr> neighbors(Representation& g, typename Representation::Vertex_ptr x) {
    std::vector<typename Representation::Vertex_ptr> n;
    for(typename Representation::Edge_ptr e : g.edges_from(x)) {
        if(e) {
            n.push_back((e->end));
        }
    }
    return n;
}

template<Graph Representation>
void add(Representation& g, typename Representation::Vertex_ptr x) {
    g.add_vertex(x);
}

template<Graph Representation>
void add_edge(Representation& g, typename  Representation::Edge_ptr e){
    g.add_edge(e);
}

template<Graph Representation>
void add_edge(Representation& g, typename  Representation::Vertex_ptr x, typename  Representation::Vertex_ptr y){
    g.add_edge(make_edge(x, y));
}

template<Graph Representation>
typename Representation::Vertex_ptr top(Representation& g){
    return g.top();
}

template<Graph Representation>
std::string toDot(Representation& g) {
    std::stringstream ss;
    ss<<"digraph G\n{\n";
    ss<<"\t# vertices:\n";
    for(auto v: g.vertices()) {
        ss <<"\t"<< toDot(v) <<"\n";
    }
    ss<<"\n";
    ss<<"\t# edges:\n";
    for(auto e: g.edges()) {
        ss <<"\t"<< toDot(e) <<"\n";
    }
    ss<<"\n";
    ss<<"\t# adjacency:\n";
    for(auto& r : g.adjacency()) {
        ss <<"\t# ";
        for(auto e : r) {
            ss << ((bool)e) <<",";
        }
        ss << "\n";
    }
    ss << "\n";
    ss << "}\n\n";
    return ss.str();

}

template<Graph Representation>
int num_vertices(Representation& g) {
    return g.num_vertices();
}

template<Graph Representation>
int num_edges(Representation& g) {
    return g.num_edges();
}

template<Graph Representation>
bool exists_cycle(Representation g, typename Representation::Vertex_ptr top) {
    const auto& v = g.vertices();
    std::set<typename Representation::Vertex_ptr> unvisited(v.begin(), v.end());

    std::stack<typename Representation::Vertex_ptr> to_visit;
    to_visit.push(top);

    while(!to_visit.empty()) {
        auto x = to_visit.top();
        to_visit.pop();
        // std::cout << "DEBUG: visiting " << toDot(x) <<"\n";
        auto it = unvisited.find(x);
        if(it != unvisited.end()) {
            for( auto y : neighbors(g,(*it))) {
                to_visit.push(y);
            }
            unvisited.erase(it);
        } else {
            return true;
        }
    }
    return false;
}
template<Graph Representation>
bool exists_cycle(Representation g) {
    return exists_cycle(g, g.top());
}
 
template<Graph Representation>
int num_non_reachable_vertices(Representation g, typename Representation::Vertex_ptr top) {
    const auto& v = g.vertices();
    std::set<typename Representation::Vertex_ptr> unvisited(v.begin(), v.end());

    std::stack<typename Representation::Vertex_ptr> to_visit;
    to_visit.push(top);

    while(!to_visit.empty()) {
        auto x = to_visit.top();
        to_visit.pop();
        // std::cout << "DEBUG: visiting " << toDot(x) <<"\n";
        auto it = unvisited.find(x);
        if(it != unvisited.end()) {
            for( auto y : neighbors(g,(*it))) {
                to_visit.push(y);
            }
            unvisited.erase(it);
        }
    }
    return unvisited.size();
}

template<Graph Representation>
bool fully_reachable(Representation g, typename Representation::Vertex_ptr top) {
    return !num_non_reachable_vertices(g, top);
} 

template<Graph Representation>
int num_non_reachable_vertices(Representation g) {
    return num_non_reachable_vertices(g, g.top());
}

template<Graph Representation>
bool fully_reachable(Representation g) {
    return fully_reachable(g, g.top());
}

//    void remove(Graph& g, Vertex_ptr x);
//    value value(Graph& g, Vertex_ptr x); // vertex value
//    void set_value(Graph& g, Vertex x, Value v); // set vertex value
//    Value value(Graph& g, Edge_ptr e); // edge value
//    void set_value(Graph& g, Edge_ptr e, Value v); // edge value

//    Write a function that lists the vertexes in order of Values (highest value first)
//    Write a function that lists the edges in order of Values (highest value first)

#endif /*__GRAPH_H__*/
