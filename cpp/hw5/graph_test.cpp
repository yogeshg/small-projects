#include"graph_defaults.h"
#include"graph.h"

// using namespace graph;

int main() {
    try {
        Adjacency_matrix<Vertex_ptr, Edge_ptr> a;
        Vertex_ptr pV1 = std::make_shared<Vertex>("foo", 1);
        Vertex_ptr pV2 = std::make_shared<Vertex>("bar", 2);
        Vertex_ptr pV3 = std::make_shared<Vertex>("baz", 3);
        Vertex_ptr pV4 = std::make_shared<Vertex>("four", 4);
        Vertex_ptr pV5 = std::make_shared<Vertex>("five", 5);
        Vertex_ptr pV6 = std::make_shared<Vertex>("six", 6);
        Vertex_ptr pV7 = std::make_shared<Vertex>("seven", 7);
        a.add(pV1);
        a.add(pV2);
        a.add(pV3);
        a.add(pV4);
        a.add(pV5);
        a.add(pV6);
        a.add(pV7);
        a.add_edge(std::make_shared<Edge>(pV1, pV3));
        a.add_edge(std::make_shared<Edge>(pV4, pV7));
        // a.add_edge(pV1, pV5);
        // a.add_edge(pV3, pV2);
        // a.add_edge(pV5, pV6);
        // a.add_edge(pV5, pV7);
        // a.add_edge(pV6, pV1);
        std::cout << a.toString() << "\n";
    } catch (const char* e) {
        std::cout << "caught exception: " << e <<"\n";
    } catch (std::string e) {
        std::cout << "caught exception: " << e <<"\n";
    }
    return 0;
}


