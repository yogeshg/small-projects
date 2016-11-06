#include<iostream>
class Node {
public:
    char val;
    int freq;
    Node* left;
    Node* right;
public:
    Node(char v)
        :val(v), freq(0), left(NULL), right(NULL) {};
    Node(char v, int f)
        :val(v), freq(f), left(NULL), right(NULL) {};
    Node(char v, int f, Node* l, Node* r)
        :val(v), freq(f), left(l), right(r) {};

    std::string toString() {
        std::string s;
        if(left) s += left->toString();
        s+=std::string(freq, val);
        if(right) s+= right->toString();
        return s;
    }

    void toCout() { return toCout(10); }
    void toCout(int n) {
        std::cout << "(";
        if(left) {
            left->toCout(n);
        }
        std::cout << val <<":"<< freq;
        if(right) {
            right->toCout(n);
        }
        std::cout << ")";
    }

    void add(char v) {return add(v, 1);}
    void add(char v, int f) {
        if(v < val) {
            if(left) {
                left->add(v, f);
            } else {
                left = new Node(v, f);
            }
        } else if (v > val) {
            if(right) {
                right->add(v, f);
            } else {
                right = new Node(v, f);
            }
        } else { // assert v == val
            freq+=f;
        }
    }
    void addNodeByFreq(Node* node) {
        if( node ) {
            addNodeByFreq( node->left );
            addNodeByFreq( node->right );
            node->left = NULL;
            node->right = NULL;
            const int f = node->freq;
            if(f > freq) {
                if(left) {
                    left->addNodeByFreq(node);
                } else {
                    left = node;
                }
            } else {
                if(right) {
                    right->addNodeByFreq(node);
                } else {
                    right = node;
                }
            }
        }
    }
};

class FreqTree {
    private:
        Node* root;
    public:
        FreqTree() : root(NULL) {};
        void add(char v) {return add(v,1);}
        void add(char v, int f) {
            if( root ) {
                root->add(v,f);
            } else {
                root = new Node(v, f);
            }
        }
        void toCout() {
            if(root) {
                root->toCout();
            } else {
                std::cout<<"()";
            }
        }

        void toFreq() {
            Node* l = root->left;
            Node* r = root->right;
            root->left = NULL;
            root->right = NULL;
            root->addNodeByFreq( l );
            root->addNodeByFreq( r );
        }
        std::string toString() {
            if( root ) {
                return root->toString();
            } else {
                return std::string("");
            }
        }
};

class Solution {
    public:
        std::string frequencySort(std::string s) {
            FreqTree t;
            // t.toCout(); std::cout<<"\n";
            for( char& c : s ) {
            //     std::cout<<c<<" ";
            t.add(c, 1);
            }
            // t.toCout(); std::cout<<"\n";
            t.toFreq();
            // t.toCout(); std::cout<<"\n";
            return t.toString();
        }
};

int main( int argc, char** argv ) {
    Solution s;
    std::string inp(argv[1]);
    std::cout << inp << "\n";
    std::cout << s.frequencySort(inp) <<"\n";

}
