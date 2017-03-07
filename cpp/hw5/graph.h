#include<sstream>
#include<string>
#include<utility>
#include<memory>
#include<vector>


typedef std::pair<std::string,int> Value;
typedef Value Vertex;
typedef std::shared_ptr<Vertex> Vertex_ptr;
typedef std::pair<Vertex_ptr, Vertex_ptr> Edge;
typedef std::shared_ptr<Edge> Edge_ptr;



namespace graph {
    void toString(Vertex v, std::ostream& ss);
    std::string toString(Vertex v);
    void toString(Edge e, std::ostream& ss);
    std::string toString(Edge e);

    class Adjacency_matrix {
        public:
            Adjacency_matrix() {}

            std::vector<std::vector<Edge_ptr>> m;        // actaual matrix
            std::vector<Vertex_ptr> vertices;       // list of vertices
            std::vector<Edge_ptr> edges;        // list of edges

            void add(Vertex_ptr x);
            void add_edge(Edge_ptr e);
            std::string toString();
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

}