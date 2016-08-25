#include <iostream>
#include <vector>
#include "util.hpp"

// Lexicographic numbers upto n

void lex(int n, int* list, int root, int& index) {
    if( root<=n ) {
        std::cerr << n <<","<< root <<"\n";
        list[++index] = root;
        root*=10;
        for( int i=0; i<10; ++i) {
            lex(n, list, root+i, index);
        }
    }
    return;
}

std::vector<int> lex(int n) {
    std::vector<int> list;
    for(int i=1; i<=n; ++i) {
        list.push_back(0);
    }
    int index = -1;
    for(int i = 1; i < 10; ++i) {
        lex(n, &list[0], i, index);
    }
    return list;
}

int main(int argc, char** argv) {
    int n = atoi(argv[1]);
    std::cerr << n <<"\n";

    std::vector<int> list = lex(n);

    yo::util::iterable2str(list);

    return 0;
}
