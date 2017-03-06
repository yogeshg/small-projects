#include"graph.h"
#include<vector>
#include<cassert>
#include<memory>
#include"util.hpp"

using namespace util;
using namespace graph;

typedef Value Vertex;
typedef std::shared_ptr<Vertex> Vertex_ptr;
typedef std::pair<Vertex_ptr, Vertex_ptr> Edge;
typedef std::shared_ptr<Edge> Edge_ptr;

class Adjacency_matrix {
    public:
        Adjacency_matrix() {}

        std::vector<std::vector<Edge_ptr>> m;        // actaual matrix
        std::vector<Vertex_ptr> vertices;       // list of vertices

        void add(Vertex_ptr x) {
            std::vector<Edge_ptr> row;
            // New vertex has no edge for any previous vertex
            for(int i=0; i<vertices.size(); ++i) {
                Edge_ptr null_edge_ptr;
                row.push_back( null_edge_ptr );               // TODO push null pointer
            }
            std::cout << "DEBUG: adding row\n";
            m.push_back(row);

            // Old vertices have no edge for new vertex
            for(std::vector<Edge_ptr>& r : m) {
                std::cout << "DEBUG: adding to row size("<<r.size()<<")";
                Edge_ptr null_edge_ptr;
                r.push_back( null_edge_ptr );
                std::cout << "to size("<<r.size()<<")\n";
            }

            // add vertex to the list
            vertices.push_back(x);            
        }
        // void add_edge(Edge_ptr e) {

        // }
        std::string toString() {
            std::stringstream ss;
            ss << "vertices:\n";
            for(auto v: vertices) {
                ss << graph::toString(*v) <<" ";
            }
            ss<<"\n";
            ss << "adjacency graph (size " << m.size() <<") : \n";
            for(auto r : m) {
                ss <<"(size " << r.size() << "): ";
                for(auto e : r) {
                    ss << ((bool)e) <<",";
                }
                ss << "\n";
            }
            ss << "\n";
            ss << "\n";
            return ss.str();
            // return toString(vertices);
        }
};

void add(Adjacency_matrix& g, Vertex_ptr x) {
    
}

int main() {
    Adjacency_matrix a;
    std::cout << a.toString();
    Vertex_ptr pV1 = std::make_shared<Vertex>();
    a.add(pV1);
    std::cout << a.toString();
    return 0;
}

