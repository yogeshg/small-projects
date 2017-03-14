#ifndef __GRAPH_REPRESENTATION_TREE_H__
#define __GRAPH_REPRESENTATION_TREE_H__

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
class Node_tree {
    public:
        typedef VP Vertex_ptr;
        typedef EP Edge_ptr;

        struct Node {
            Vertex_ptr x;
            std::shared_ptr<Node> parent; 
            std::vector<std::shared_ptr<Node>> neighbors; 
            std::vector<Edge_ptr> edges;
            Node(Vertex_ptr x1, std::shared_ptr<Node> p) : parent(p), x(x1), neighbors(), edges() {}
            void clear() {
                parent = nullptr;
                x = nullptr;
                neighbors.clear();
                edges.clear();
            }
        };

        Node_tree() : root(nullptr), vertex2node(), name("Node_tree") {}
        void clear() {
            // std::cout << "DEBUG: washing away all sins\n";
            for(auto it=vertex2node.begin(); it!=vertex2node.end(); ++it) {
                auto n = it->second;
                n->clear();
            }
            vertex2node.clear();
        }
        ~Node_tree() {
            clear();
        }

    public:
        void add_vertex(Vertex_ptr x) {
            // std::cout << "DEBUG: adding a new vertex\n";
            auto it = vertex2node.find(x);
            if(it==vertex2node.end()) {
                auto p = std::make_shared<Node>(x, nullptr);
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
            const auto p_start_node = find_vertex(e->start);
            const auto p_end_node = find_vertex(e->end);
            if( (p_end_node->parent != nullptr) || (root==p_end_node) ) {
                throw "Can not make this edge in a tree.";
            }
            p_start_node->neighbors.push_back(p_end_node);
            p_start_node->edges.push_back(e);
            p_end_node->parent = p_start_node;

        };
        void remove(Vertex_ptr v) {
            const auto p = find_vertex(v);
            const bool is_root = (root==p);
            // remove reference from children, make them root if reqd
            for(auto q: p->neighbors) {
                if(is_root) {
                    root = q;
                }
                q->parent = nullptr;
            }
            // remove reference from parent
            if(p->parent) {
                const int num_siblings = p->parent->neighbors.size();
                int index_sibling = num_siblings;
                for(int i = 0; i <num_siblings; ++i){
                    if(p->parent->edges.at(i)->end==v) {
                        index_sibling = i;
                        break;
                    }
                }
                if(index_sibling >= num_siblings) {
                    throw "Vertex should be a child of parent.";
                }
                p->parent->edges.erase(p->parent->edges.begin() + index_sibling);
                p->parent->neighbors.erase(p->parent->neighbors.begin() + index_sibling);
            }
            // clear current node
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
                const auto it_parent = node2index.find(p_node->parent);
                if( it_parent != node2index.end() ) {
                    const auto index_parent = it_parent->second;
                    adjacency_matrix[index_parent][index] = true;
                }
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
                std::stringstream ss;
                ss << "Trying to find a vertex that does not exist." <<toDot(x1);
                throw ss.str();

            }
            return i->second;
        }

};

#endif /*__GRAPH_REPRESENTATION_TREE_H__*/
