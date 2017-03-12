#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<sstream>
#include<string>
#include<utility>
#include<vector>
#include<iostream>
#include<algorithm>

template< template<typename, typename>class Representation, typename Vertex_ptr, typename Edge_ptr>
concept bool Graph = requires(Representation<Vertex_ptr, Edge_ptr> r, Vertex_ptr vp, Edge_ptr ep) {
    {r.add_vertex(vp)} -> void;
    {r.add_edge(ep)} -> void;
    {r.edges()} -> std::vector<Edge_ptr>;
    {r.edges_from(vp)} -> std::vector<Edge_ptr>;
    {r.vertices()} -> std::vector<Vertex_ptr>;
    {ep->start} -> Vertex_ptr;
    {ep->end} -> Vertex_ptr;
    {r.adjacent(vp, vp)} -> bool;
    {r.top()} -> Vertex_ptr;
};

    template<template<typename, typename>class Representation, typename Vertex_ptr, typename Edge_ptr>
void add(Representation<Vertex_ptr, Edge_ptr>& g, Vertex_ptr x)
    requires Graph<Representation, Vertex_ptr, Edge_ptr>
{
    g.add_vertex(x);
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
