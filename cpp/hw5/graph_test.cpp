# include"graph_defaults.h"
# include"graph_representation.h"
# include"graph_representation_tree.h"
# include"graph.h"
#include<iostream>
#include<fstream>

class Log
{
    std::ofstream byname;
    std::ostream& fos;
    std::ostream& sos;
    bool some_error;
    bool to_close;
    public:
    Log(std::string filename) : some_error(false), to_close(false), byname(filename), fos(this->byname), sos(std::cout)
    {
        if (!fos) {
            some_error = true;
        }
    }
    std::ostream& get_os() {
        if(some_error) return sos;
        else return fos;
    }
    ~Log() {
        // if(to_close)
        //     fos.close();
    }
};

void test(Graph& a, std::string report_filename="", std::string graph_filename="") {
    auto& out = std::cout;
    Log g_all("g_all.dot");
    Log g_rem("g_rem.dot");
    Log r(report_filename);
    try {
        r.get_os() << "# " << "testing graph "<<a.name<<"\n";
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
        try {add_edge(a, pV3, pV5);} catch (const char*e) {r.get_os() << "# " << "caught exception "<< e <<"\n"; }
        add_edge(a, pV5, pV6);
        try {add_edge(a, pV5, pV7);} catch (const char*e) {r.get_os() << "# " << "caught exception "<< e <<"\n"; }
        try {add_edge(a, pV6, pV1);} catch (const char*e) {r.get_os() << "# " << "caught exception "<< e <<"\n"; }
        g_all.get_os()<< toDot(a) << "\n";
        // a.remove(pV5);
        a.remove(pV1);
        a.remove(pV3);
        g_rem.get_os()<< toDot(a) << "\n";
        r.get_os() << "# " << "top element is: " << toDot(top(a)) <<"\n";
        r.get_os() << "# " << "neighbors of "<<toDot(pV3) << " are: "<< a.edges_from(pV3).size() <<"\n";
        r.get_os() << "# " << "number of vertices not reachable form this are: "<< num_non_reachable_vertices(a)<<"\n";
        r.get_os() << "# " << "number of vertices not reachable form "<< toDot(pV6)  <<" are: "<< num_non_reachable_vertices(a, pV6)<<"\n";
        r.get_os() << "# " << "number of vertices not reachable form "<< toDot(pV7)  <<" are: "<< num_non_reachable_vertices(a, pV7)<<"\n";
        r.get_os() << "# " << "number of vertices not reachable form "<< toDot(pV3)  <<" are: "<< num_non_reachable_vertices(a, pV3)<<"\n";
        r.get_os() << "# " << "is this graph fully reachable?: "<< fully_reachable(a) <<"\n";
        r.get_os() << "# " << "is this graph fully reachable from "<< toDot(pV7) <<"?: "<< fully_reachable(a, pV7) <<"\n";
        r.get_os() << "# " << "top element is: " << toDot(top(a)) <<"\n";
        r.get_os() << "# " << "is there a cycle?: "<< exists_cycle(a) <<"\n";
        r.get_os() << "# " << "is there a cycle from "<< toDot(pV4) <<"?: "<< exists_cycle(a, pV4) <<"\n";

        r.get_os() << "# " << "are " << toDot(pV5) << " and "<< toDot(pV6) <<" adjacent? : " << a.adjacent(pV5, pV6) <<"\n";
        r.get_os() << "# " << "are " << toDot(pV5) << " and "<< toDot(pV1) <<" adjacent? : " << a.adjacent(pV5, pV1) <<"\n";
    } catch (const char* e) {
        r.get_os() << "# " << "caught exception: " << e <<"\n";
    } catch (std::string e) {
        r.get_os() << "# " << "caught exception: " << e <<"\n";
    }

}

int main() {
    // Adjacency_matrix<Vertex_ptr, Edge_ptr> a1;
    // test(a1, "", "");
    Node_graph<Vertex_ptr, Edge_ptr> a2;
    test(a2, "", "");
    // Node_tree<Vertex_ptr, Edge_ptr> a3;
    // test(a3, "", "");
    return 0;
}


