#include"graph.h"
#include"graph_defaults.h"
#include<memory>

Edge_ptr make_edge_ptr(Vertex_ptr s, Vertex_ptr e) {
    return std::make_shared<Edge>(s, e);
}

std::string toLabel(const Value& v) {
    std::stringstream ss;
    ss <<"[label=\"" << v.first <<":"<<v.second<<"\"]";
    return ss.str();
}
std::string toId(Vertex_ptr v) {
    std::stringstream ss;
    ss <<"v"<<v;
    return ss.str();
}

std::string toDot(Vertex_ptr v) {
    std::stringstream ss;
    ss << toId(v) << " " << toLabel(*v) << ";";
    return ss.str();
}
std::string toDot(Edge_ptr e) {
    std::stringstream ss;
    ss << toId(e->start) << " -> " << toId(e->end) << " " << toLabel(e->value) << ";";
    return ss.str();
}
