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

void test1(Graph& a, std::string report_prefix="", std::string graph_prefix="") {
    auto& out = std::cout;
    Log r(report_prefix + ".txt");
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
        r.get_os() << "# " << "value of " <<toDot(pV6)<<" is "<< toLabel(*pV6) <<"\n";
        *pV6 = {"six", 600};
        e->value = {"myedge", 2};
        r.get_os() << "# " << "value of " <<toDot(pV6)<<" is "<< toLabel(*pV6) <<"\n";
        r.get_os() << "# " << "value of " <<toDot(e)<<" is "<< toLabel(e->value) <<"\n";
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
        r.get_os() << "# sorted vertices:\n";
        for(Vertex x: sorted_vertices(a)) {
            r.get_os() <<"#\t"<< toLabel(x)<<"\n";
        }
        r.get_os() << "# sorted edges:\n";
        for(Edge e: sorted_edges(a)) {
            r.get_os() <<"#\t"<< toLabel(e.value)<<"\n";
        }
    } catch (const char* e) {
        r.get_os() << "# " << "caught exception: " << e <<"\n";
    } catch (std::string e) {
        r.get_os() << "# " << "caught exception: " << e <<"\n";
    }

}


void test2(Graph& a, std::string report_prefix="", std::string graph_prefix="") {
    auto& out = std::cout;
    Log g_all(graph_prefix + "_all.dot");
    Log g_rem(graph_prefix + "_rem.dot");
    try {
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
        try {add_edge(a, pV3, pV5);} catch (const char*e) {std::cout << "# " << "caught exception "<< e <<"\n"; }
        add_edge(a, pV5, pV6);
        try {add_edge(a, pV5, pV7);} catch (const char*e) {std::cout << "# " << "caught exception "<< e <<"\n"; }
        try {add_edge(a, pV6, pV1);} catch (const char*e) {std::cout << "# " << "caught exception "<< e <<"\n"; }
        *pV6 = {"six", 600};
        e->value = {"myedge", 2};
        g_all.get_os()<< toDot(a) << "\n";
        // a.remove(pV5);
        try{ a.remove(pV1); } catch(...){};
        try{ a.remove(pV3); } catch(...){};
        g_rem.get_os()<< toDot(a) << "\n";
    } catch (const char* e) {
    } catch (std::string e) {
    }

}

int main() {
    {
        Adjacency_matrix<Vertex_ptr, Edge_ptr> a1;
        test1(a1, "out/r1", "out/g1");
        Node_graph<Vertex_ptr, Edge_ptr> a2;
        test1(a2, "out/r2", "out/g2");
        Node_tree<Vertex_ptr, Edge_ptr> a3;
        test1(a3, "out/r3", "out/g3");
    } {
        Adjacency_matrix<Vertex_ptr, Edge_ptr> a1;
        test2(a1, "out/r1", "out/g1");
        Node_graph<Vertex_ptr, Edge_ptr> a2;
        test2(a2, "out/r2", "out/g2");
        Node_tree<Vertex_ptr, Edge_ptr> a3;
        test2(a3, "out/r3", "out/g3");
    }
    return 0;
}


