#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Hello World" << "\n";
    for( int i=0; i<argc; ++i) {
        std::cout << argv[i] << " ";
    }
    std::cout << "\n";
    return 0;
}
