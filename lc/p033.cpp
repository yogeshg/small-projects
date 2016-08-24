#include <iostream>
#include <vector>
#include "util.hpp"

// Lexicographic numbers upto n

void lex(int n, int root, std::vector<int>& list) {
    if( root<=n ) {
        std::cout << n <<","<< root <<"\n";
        list.push_back(root);
        root*=10;
        for( int i=0; i<10; ++i) {
            lex(n, root+i, list);
        }
    }
    return;
}

int main(int argc, char** argv) {
    int N = atoi(argv[1]);
    std::cout << N <<"\n";

    int index = -1;
    std::vector<int> list;

    for(int i = 1; i < 10; ++i) {
        lex(N, i, list);
    }

    yo::util::iterable2str(list);

    std::cout << "\n";
    return 0;
}
