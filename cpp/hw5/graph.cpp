#include"graph.h"
#include<cassert>
#include<iostream>
#include"util.hpp"
#include<algorithm>

using namespace graph;

void graph::toString(Vertex v, std::ostream& ss) {
    ss << v.second <<"(" << v.first <<")";
}
std::string graph::toString(Vertex v) {
    std::stringstream ss;
    toString(v, ss);
    return ss.str();
}

void graph::toString(Edge e, std::ostream& ss) {
    ss << graph::toString(*e.first) <<"->"<< graph::toString(*e.second);
}
std::string graph::toString(Edge e) {
    std::stringstream ss;
    graph::toString(e, ss);
    return ss.str();
}


void graph::Adjacency_matrix::add(Vertex_ptr x) {
            std::vector<Edge_ptr> row;
            // New vertex has no edge for any previous vertex
            for(int i=0; i<vertices.size(); ++i) {
                Edge_ptr null_edge_ptr;
                row.push_back( null_edge_ptr );               // TODO push null pointer
            }
            m.push_back(row);

            // Old vertices have no edge for new vertex
            for(auto& r : m) {
                Edge_ptr null_edge_ptr;
                r.push_back( null_edge_ptr );
            }

            // add vertex to the list
            vertices.push_back(x);
        }

void graph::Adjacency_matrix::add_edge(Edge_ptr e) {
    edges.push_back(e);
    int i, j = 0;
    for(i=0; i<vertices.size(); ++i) {
        if(vertices.at(i) == e->first) {
            break;
        }
    }
    for(j=0; j<vertices.size(); ++j) {
        if(vertices.at(j) == e->second) {
            break;
        }
    }
    if( (i>=vertices.size()) || (j>=vertices.size()) ) {
        throw "Edge contains a vertex that is not in Graph.";
    }
    m.at(i).at(j) = e;
    // (edges.size()-1);
}

std::string graph::Adjacency_matrix::toString() {
            std::stringstream ss;
            ss << "vertices:\n";
            for(auto v: vertices) {
                ss << graph::toString(*v) <<" ";
            }
            ss<<"\n";
            ss << "edges:\n";
            for(auto e: edges) {
                ss << graph::toString(*e) <<" ";
            }
            ss<<"\n";
            ss << "adjacency graph (size " << m.size() <<") : \n";
            for(auto& r : m) {
                ss <<"(size " << r.size() << "): ";
                for(auto e : r) {
                    ss << ((bool)e) <<",";
                }
                ss << "\n";
            }
            ss << "\n";
            ss << "\n";
            return ss.str();
        }


int main() {
    Adjacency_matrix a;
    std::cout << a.toString();
    Vertex_ptr pV1 = std::make_shared<Vertex>("foo", 1);
    Vertex_ptr pV2 = std::make_shared<Vertex>("bar", 2);
    Vertex_ptr pV3 = std::make_shared<Vertex>("baz", 3);
    a.add(pV1);
    a.add(pV2);
    a.add(pV3);
    Edge_ptr pE1 = std::make_shared<Edge>(pV1, pV3);
    a.add_edge(pE1);
    std::cout << a.toString();
    return 0;
}
