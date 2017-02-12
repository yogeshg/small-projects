#include<iostream>
#include<random>
#include<sstream>

int main(int argc, char** argv) {
    int size;
    int seed;
    try {
        std::istringstream(argv[1]) >> size;
        std::istringstream(argv[2]) >> seed;
    } catch(...) {
        std::cerr << "usage:\n\t"<<argv[0]<<" size seed\n";
        return 1;
    }

    std::default_random_engine generator(seed);
    std::vector<std::uniform_int_distribution<int>> distributions;
    for(int curr=size; curr>0; --curr){
        distributions.push_back(std::uniform_int_distribution<int>((curr-1)*100,curr*100));
    }

    for( int i=0; i<size; ++i) {
        std::cout << distributions[i](generator) << "  ";
    }
    std::cout << "Hello World\n";
    return 0;
}
