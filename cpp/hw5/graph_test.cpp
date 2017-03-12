#include"graph_defaults.h"
#include"graph_representation.h"
#include"graph.h"

int main() {
    try {
        //Adjacency_matrix<Vertex_ptr, Edge_ptr> a;
        Node_graph<Vertex_ptr, Edge_ptr> a;
        Vertex_ptr pV1 = std::make_shared<Vertex>("foo", 1);
        Vertex_ptr pV2 = std::make_shared<Vertex>("bar", 2);
        Vertex_ptr pV3 = std::make_shared<Vertex>("baz", 3);
        Vertex_ptr pV4 = std::make_shared<Vertex>("four", 4);
        Vertex_ptr pV5 = std::make_shared<Vertex>("five", 5);
        Vertex_ptr pV6 = std::make_shared<Vertex>("six", 6);
        Vertex_ptr pV7 = std::make_shared<Vertex>("seven", 7);
        add(a, pV1);
        add(a, pV2);
        add(a, pV3);
        add(a, pV4);
        add(a, pV5);
        add(a, pV6);
        add(a, pV7);
        auto e = std::make_shared<Edge>(pV1, pV3);
        a.add_edge(e);
        a.add_edge(std::make_shared<Edge>(pV4, pV7));
        add_edge(a, pV1, pV5);
        add_edge(a, pV3, pV2);
        add_edge(a, pV5, pV6);
        add_edge(a, pV5, pV7);
        add_edge(a, pV6, pV1);
        add_edge(a, pV2, pV4);
        std::cout << toDot(a) << "\n";
        std::cout << "top element is: " << toDot(top(a)) <<"\n";
        std::cout << "neighbors of "<<toDot(pV3) << " are: "<< a.edges_from(pV3).size() <<"\n";
        std::cout << "number of vertices not reachable form this are: "<< num_non_reachable_vertices(a)<<"\n";
        std::cout << "number of vertices not reachable form "<< toDot(pV6)  <<" are: "<< num_non_reachable_vertices(a, pV6)<<"\n";
        std::cout << "number of vertices not reachable form "<< toDot(pV7)  <<" are: "<< num_non_reachable_vertices(a, pV7)<<"\n";
        std::cout << "number of vertices not reachable form "<< toDot(pV3)  <<" are: "<< num_non_reachable_vertices(a, pV3)<<"\n";
        std::cout << "is this graph fully reachable?: "<< fully_reachable(a) <<"\n";
        std::cout << "is this graph fully reachable from "<< toDot(pV7) <<"?: "<< fully_reachable(a, pV7) <<"\n";
        std::cout << "is there a cycle?: "<< exists_cycle(a) <<"\n";
        std::cout << "is there a cycle from "<< toDot(pV4) <<"?: "<< exists_cycle(a, pV4) <<"\n";
    } catch (const char* e) {
        std::cout << "caught exception: " << e <<"\n";
    } catch (std::string e) {
        std::cout << "caught exception: " << e <<"\n";
    }
    return 0;
}


