#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<sstream>
#include<string>
#include<utility>
#include<vector>
#include<iostream>
#include<algorithm>

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
};

template<Graph Representation>
bool adjacent(Representation& g, typename Representation::Vertex_ptr x, typename Representation::Vertex_ptr y) {
    return g.adjacent(x, y);
}
template<Graph Representation>
bool neighbors(Representation& g, typename Representation::Vertex_ptr x) {
    return g.neighbors(x);
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


//    bool adjacent(Graph& g, Vertex_ptr x, Vertex_ptr y);
//    bool neighbors(Graph& g, Vertex_ptr x);
//    void add(Graph& g, Vertex_ptr x);
//    void remove(Graph& g, Vertex_ptr x);
//    void add_edge(Grap&h g, Vertex_ptr x, Vertex_ptr y);
//    void add_edge(Graph& g, Edge_ptr e); // and edge is a pair of vertexes
//    value value(Graph& g, Vertex_ptr x); // vertex value
//    void set_value(Graph& g, Vertex x, Value v); // set vertex value
//    Value value(Graph& g, Edge_ptr e); // edge value
//    void set_value(Graph& g, Edge_ptr e, Value v); // edge value
//    Vertex top(Graph&); // get some Vertex



//    Write a function that prints a graph in some format (e.g., as text)
//    Write a function that counts the number of vertexes
//    Write a function that counts the number of edges
//    Write a function that check if every vertex is reachable from the top
//    Write a function that finds cycles
//    Write a function that lists the vertexes in order of Values (highest value first)
//    Write a function that lists the edges in order of Values (highest value first)

#endif /*__GRAPH_H__*/
