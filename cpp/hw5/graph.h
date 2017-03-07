#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<sstream>
#include<string>
#include<utility>
#include<memory>
#include<vector>
#include<iostream>
#include<algorithm>

// namespace graph {

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

    // namespace dot {

        std::string toLabel(const Value& v);
        std::string toId(Vertex_ptr v);
        std::string toDot(Vertex_ptr v);
        std::string toDot(Edge_ptr e);

        template<typename T>
        concept bool DotRepresntable = requires(T a){
            {toDot(a)} -> std::string;
        };
    // }

    // For the following class, (Vertex_ptr, Edge_ptr) are templatized
    template <DotRepresntable Vertex_ptr, DotRepresntable Edge_ptr>
    class Adjacency_matrix {
        public:
            Adjacency_matrix() {}

            void add(Vertex_ptr x) {
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


            void add_edge(Edge_ptr e){
                edges.push_back(e);
                int i, j = 0;
                for(i=0; i<vertices.size(); ++i) {
                    if(vertices.at(i) == e->start) {
                        break;
                    }
                }
                for(j=0; j<vertices.size(); ++j) {
                    if(vertices.at(j) == e->end) {
                        break;
                    }
                }
                if( (i>=vertices.size()) || (j>=vertices.size()) ) {
                    throw "Edge contains a vertex that is not in Graph.";
                }
                m.at(i).at(j) = e;
                // (edges.size()-1);
            };
            void add_edge(Vertex_ptr x, Vertex_ptr y){
                add_edge(std::make_shared<Edge>(x, y));
            }

            std::string toString() {
                std::stringstream ss;
                ss<<"digraph G\n{\n";
                ss<<"\t# vertices:\n";
                for(auto v: vertices) {
                    ss <<"\t"<< toDot(v) <<"\n";
                }
                ss<<"\n";
                ss<<"\t# edges:\n";
                for(auto e: edges) {
                    ss <<"\t"<< toDot(e) <<"\n";
                }
                ss<<"\n";
                ss<<"\t# adjacency:\n";
                for(auto& r : m) {
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

            int num_edges() {return edges.size();};
            int num_vertices() {return vertices.size();};
        private:
            std::vector<std::vector<Edge_ptr>> m;           // actaual matrix
            std::vector<Vertex_ptr> vertices;               // list of vertices
            std::vector<Edge_ptr> edges;                    // list of edges

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

// }

#endif /*__GRAPH_H__*/