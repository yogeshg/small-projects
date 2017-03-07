#ifndef __GRAPH_DEFAULTS_H__
#define __GRAPH_DEFAULTS_H__

#include<memory>

typedef std::pair<std::string,int> Value;
typedef Value Vertex;
typedef std::shared_ptr<Vertex> Vertex_ptr;
// typedef std::pair<Vertex_ptr, Vertex_ptr> Edge;
// typedef std::tuple<Vertex_ptr, Vertex_ptr, Value> Edge2;
struct Edge {
    Vertex_ptr start;
    Vertex_ptr end;
    Value value;
    Edge(Vertex_ptr s, Vertex_ptr e) : start(s), end(e), value("",1) {}
};

typedef std::shared_ptr<Edge> Edge_ptr;

std::string toLabel(const Value& v);
std::string toId(Vertex_ptr v);
std::string toDot(Vertex_ptr v);
std::string toDot(Edge_ptr e);

#endif /* __GRAPH_DEFAULTS_H__ */
