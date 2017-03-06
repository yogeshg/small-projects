#include"graph.h"
#include<vector>
#include<cassert>
#include<memory>

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
            m.push_back(row);

            // Old vertices have no edge for new vertex
            for(auto r : m) {
                Edge_ptr null_edge_ptr;
                r.push_back( null_edge_ptr );
            }

            // add vertex to the list
            vertices.push_back(x);            
        }
        // void add_edge(Edge_ptr e) {

        // }
};

void add(Adjacency_matrix& g, Vertex_ptr x) {
    
}

int main() {
    Adjacency_matrix a;
    auto pV1 = std::make_shared<Vertex>;
    return 0;
}

