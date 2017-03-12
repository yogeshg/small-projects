#ifndef __GRAPH_REPRESENTATION_H__
#define __GRAPH_REPRESENTATION_H__

#include<sstream>
#include<string>
#include<utility>
#include<vector>
#include<iostream>
#include<algorithm>

template <class VP, class EP>
class Adjacency_matrix {
    public:
        typedef VP Vertex_ptr;
        typedef EP Edge_ptr;

        Adjacency_matrix() {}

        void add_vertex(Vertex_ptr x) {
            std::vector<Edge_ptr> row;
            // New vertex has no edge for any previous vertex
            for(int i=0; i<num_vertices(); ++i) {
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
            vertex_list.push_back(x);
        }

        void add_edge(Edge_ptr e){
            edge_list.push_back(e);
            int i, j = 0;
            i = find_vertex(e->start);
            j = find_vertex(e->end);
            if( (i>=num_vertices()) || (j>=num_vertices()) ) {
                throw "Edge contains a vertex that is not in Graph.";
            }
            m.at(i).at(j) = e;
        };
        int num_edges() {return edge_list.size();};
        int num_vertices() {return vertex_list.size();};

        bool adjacent(Vertex_ptr x1, Vertex_ptr x2) {
            int i = find_vertex(x1);
            int j = find_vertex(x2);
            if( i<num_vertices() && j<num_vertices() ) {
                return (bool)m.at(find_vertex(x1)).at(find_vertex(x2));
            }
            return false;
        }
        
        std::vector<Edge_ptr> edges_from(Vertex_ptr x1) {
            std::vector<Edge_ptr> list_of_edges;
            int i = find_vertex(x1);
            if( i<num_vertices() ) {
                for(auto e : m.at(i)) {
                    list_of_edges.push_back(e);
                }
            }
            return list_of_edges;
        }

        std::vector<Edge_ptr> edges() {
            return edge_list;
        }
        std::vector<Vertex_ptr> vertices() {
            return vertex_list;
        }
        std::vector<std::vector<bool>> adjacency() {
            const int n = num_vertices();
            std::vector<std::vector<bool>> adjacency_matrix(n, std::vector<bool>(n, false));
            int i=0; 
            for(auto l : m){
                int j = 0;
                for(auto e : l){
                    adjacency_matrix[i][j]=(bool)e;
                    ++j;
                }
                ++i;
            }
            return adjacency_matrix;
        }

        Vertex_ptr top() {
            return vertex_list[0];
        }
    private:
        std::vector<std::vector<Edge_ptr>> m;           // actaual matrix
        std::vector<Vertex_ptr> vertex_list;               // list of vertices
        std::vector<Edge_ptr> edge_list;                    // list of edges

    private:
        int find_vertex(const Vertex_ptr& x) {
            int i=0;
            for(i=0; i<num_vertices(); ++i){
                if(vertex_list.at(i) == x) {
                    return i;
                }
            }
            return i;
        }
};

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

#endif /*__GRAPH_REPRESENTATION_H__*/
