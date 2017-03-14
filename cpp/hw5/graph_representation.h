#ifndef __GRAPH_REPRESENTATION_H__
#define __GRAPH_REPRESENTATION_H__

#include<sstream>
#include<string>
#include<utility>
#include<vector>
#include<iostream>
#include<algorithm>
#include<map>
#include<utility>
#include<memory>
#include<stack>
#include<set>

template <class VP, class EP>
class Adjacency_matrix {
    public:
        typedef VP Vertex_ptr;
        typedef EP Edge_ptr;

        Adjacency_matrix():name("Adjacency_matrix") {}

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
            int i, j = 0;
            i = find_vertex(e->start);
            j = find_vertex(e->end);
            if( (i>=num_vertices()) || (j>=num_vertices()) ) {
                throw "Edge contains a vertex that is not in Graph.";
            }
            m.at(i).at(j) = e;
        };

        void remove(Vertex_ptr v) {
            auto i = find_vertex(v);
            for(auto& row : m) {
                Edge_ptr null_edge_ptr;
                row[i] = null_edge_ptr;
            }
            for(auto& e: m.at(i)) {
                Edge_ptr null_edge_ptr;
                e = null_edge_ptr;
            }
            Vertex_ptr null_vertex_ptr;
            vertex_list[i] = null_vertex_ptr;
        }

        int num_edges() const {return edges().size();};
        int num_vertices() const {return vertex_list.size();};

        bool adjacent(Vertex_ptr x1, Vertex_ptr x2) const {
            int i = find_vertex(x1);
            int j = find_vertex(x2);
            if( i<num_vertices() && j<num_vertices() ) {
                return (bool)m.at(find_vertex(x1)).at(find_vertex(x2));
            }
            return false;
        }

        std::vector<Edge_ptr> edges_from(Vertex_ptr x1) const {
            std::vector<Edge_ptr> list_of_edges;
            int i = find_vertex(x1);
            if( i<num_vertices() ) {
                for(auto e : m.at(i)) {
                    if(e) {
                        list_of_edges.push_back(e);
                    }
                }
            }
            return list_of_edges;
        }

        std::vector<Edge_ptr> edges() const {
            std::vector<Edge_ptr> edge_list;
            for(auto& row : m) {
                for(auto& edge : row) {
                    if(edge) {
                        edge_list.push_back(edge);
                    }
                }
            }
            return edge_list;
        }
        std::vector<Vertex_ptr> vertices() const {
            std::vector<Vertex_ptr> notnull_vertex_list;
            for(auto& x: vertex_list) {
                if(x) {
                    notnull_vertex_list.push_back(x);
                }
            }
            return notnull_vertex_list;
        }
        std::vector<std::vector<bool>> adjacency() const {
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

        Vertex_ptr top() const {
            return vertex_list[0];
        }
        const std::string name;
    private:
        std::vector<std::vector<Edge_ptr>> m;           // actaual matrix
        std::vector<Vertex_ptr> vertex_list;               // list of vertices

        int find_vertex(const Vertex_ptr& x) const {
            int i=0;
            for(i=0; i<num_vertices(); ++i){
                if(vertex_list.at(i) == x) {
                    return i;
                }
            }
            std::stringstream ss;
            ss << "Looking for a vertex ("<< toDot(x) <<") which has not been registered.";
            throw ss.str(); 
        }
};


template <class VP, class EP>
class Node_graph {
    public:
        typedef VP Vertex_ptr;
        typedef EP Edge_ptr;

        struct Node {
            Vertex_ptr x;
            std::vector<std::shared_ptr<Node>> neighbors; 
            std::vector<Edge_ptr> edges;
            Node(Vertex_ptr x1) : x(x1), neighbors(), edges() {}
            void clear() {
                x = nullptr;
                neighbors.clear();
                edges.clear();
            }
        };

        Node_graph() : root(nullptr), vertex2node(), name("Node_graph") {}
        void clear() {
            // std::cout << "DEBUG: washing away all sins\n";
            for(auto it=vertex2node.begin(); it!=vertex2node.end(); ++it) {
                auto n = it->second;
                n->clear();
            }
            vertex2node.clear();
        }
        ~Node_graph() {
            clear();
        }

        void add_vertex(Vertex_ptr x) {
            // std::cout << "DEBUG: adding a new vertex\n";
            auto it = vertex2node.find(x);
            if(it==vertex2node.end()) {
                auto p = std::make_shared<Node>(x);
                vertex2node.insert(std::make_pair(x, p));
                if(!root) {
                    root = p;
                }
            } else {
                throw "Vertex already added in the graph";
            }
        }

        void add_edge(Edge_ptr e){
            // std::cout << "DEBUG: adding edge.\n";
            auto i = vertex2node.find(e->start);
            auto j = vertex2node.find(e->end);

            if( (i==vertex2node.end()) || (j==vertex2node.end()) ) {
                throw "Edge contains a vertex that is not in Graph.";
            }

            i->second->neighbors.push_back(j->second);
            i->second->edges.push_back(e);

        };

        void remove(Vertex_ptr v) {
            const auto p = find_vertex(v);
            const bool is_root = (root==p);
            // remove reference from children, make them root if required
            for(auto q: p->neighbors) {
                if(is_root) {
                    root = q;
                }
                // They do not have a reference to the parent
            }
            // remove reference from parent
            const auto all_vertices = vertices();
            for(auto x: all_vertices) {
                auto q = find_vertex(x);
                const int num_children = q->neighbors.size();
                int index_child = num_children;
                for(auto i = 0; i < num_children; ++i) {
                    if(q->edges.at(i)->end == v) {
                        index_child = i;
                        // std::cout << "DEBUG: found a parent" << toDot(x) << "with child num "<< index_child <<" \n";
                        // std::cout << "DEBUG: lengths of neighbors is "<< q->neighbors.size()
                        //     << " and edges is " << q->edges.size() << "\n";
                        q->neighbors.erase(q->neighbors.begin() + index_child);
                        q->edges.erase(q->edges.begin() + index_child);
                        break;
                    }
                }
            }
            p->clear();
        }

        int num_edges() const {return edges().size();};
        int num_vertices() const {return vertices().size();};

        bool adjacent(Vertex_ptr x1, Vertex_ptr x2) const {
            auto p_start = find_vertex(x1);
            auto p_end = find_vertex(x2);
            auto it = std::find(p_start->neighbors.begin(), p_start->neighbors.end(), p_end);
            return it!=p_start->neighbors.end();
        }

        std::vector<Edge_ptr> edges_from(Vertex_ptr x1) const {
            auto it = find_vertex(x1);
            std::vector<Edge_ptr> list_of_edges;
            return it->edges;
        }

        std::vector<Edge_ptr> edges() const {
            std::vector<Edge_ptr> all_edges;
            std::set<std::shared_ptr<Node>> visited;
            std::stack<std::shared_ptr<Node>> to_visit;
            if(root)
                to_visit.push(root);
            while(!to_visit.empty()){
                auto n = to_visit.top();
                to_visit.pop();
                // std::cout << "DEBUG: visiting " <<toDot(n->x) << "\n";
                auto it = visited.find(n);
                if(it==visited.end()) {
                    for(auto e: n->edges) {
                        all_edges.push_back(e);
                    }
                    for(auto m: n->neighbors) {
                        to_visit.push(m);
                    }
                    visited.insert(n);
                } else {

                }
            }
            return all_edges;
        }

        std::vector<Vertex_ptr> vertices(bool debug=false) const{
            std::vector<Vertex_ptr> all_vertices;
            std::set<std::shared_ptr<Node>> visited;
            std::stack<std::shared_ptr<Node>> to_visit;
            if(root)
                to_visit.push(root);
            while(!to_visit.empty()){
                auto n = to_visit.top();
                to_visit.pop();
                // std::cout << "DEBUG: visiting " <<toDot(n->x) << "\n";
                auto it = visited.find(n);
                if(it==visited.end()) {
                    all_vertices.push_back(n->x);
                    for(auto m: n->neighbors) {
                        to_visit.push(m);
                    }
                    visited.insert(n);
                } else {

                }
            }
            if(!debug)
                return all_vertices;

            std::vector<Vertex_ptr> vertex_list;
            for(auto it = vertex2node.begin(); it!=vertex2node.end(); ++it) {
                vertex_list.push_back(it->first);
            }
            // std::cout << "DEBUG: found "<< vertex_list.size()-all_vertices.size() <<" extra nodes.\n";
            return vertex_list;
        }
        std::vector<std::vector<bool>> adjacency() const {
            std::map<std::shared_ptr<Node>, int> node2index;
            int i = 0;
            for( auto it=vertex2node.begin(); it!=vertex2node.end(); ++it) {
                const auto p_node = it->second;
                node2index[p_node] = i;
                ++i;
            }
            std::vector<std::vector<bool>> adjacency_matrix(i, std::vector<bool>(i, false));
            for( auto it=node2index.begin(); it!=node2index.end(); ++it) {
                const auto p_node = it->first;
                const auto index = it->second;
                for( auto it2 : p_node->neighbors ) {
                    auto it_child = node2index.find(it2);
                    if(it_child!=node2index.end()){
                        const auto index_child = it_child->second;
                        adjacency_matrix[index][index_child] = true;
                    }
                }
                // const auto it_parent = node2index.find(p_node->parent);
                // if( it_parent != node2index.end() ) {
                //     const auto index_parent = it_parent->second;
                //     adjacency_matrix[index_parent][index] = true;
                // }
            }
            return adjacency_matrix;
        }

        Vertex_ptr top() const {
            if(root)
                return root->x;
            else
                return nullptr;
        }

        const std::string name;
    private:
        std::shared_ptr<Node> root;
        std::map<Vertex_ptr, std::shared_ptr<Node>> vertex2node;
        std::shared_ptr<Node> find_vertex(const Vertex_ptr& x1) const {
            auto i = vertex2node.find(x1);
            if( i==vertex2node.end() ) {
                throw "Trying to find a vertex that does not exist.";
            }
            return i->second;
        }
};

#endif /*__GRAPH_REPRESENTATION_H__*/
