#include<vector>
#include<random>
// #include<chrono>
#include<string>
#include<sstream>
#include<iostream>
#include"util.hpp"

using namespace util;

std::vector<int>::iterator find_geq(std::vector<int>::iterator beg,std::vector<int>::iterator end, int val) {
    while( beg!=end ) {
        if( *beg < val ) {
            ++beg;
        } else {
            break;
        }
    }
    return beg;
}
void insert_ordered(std::vector<int>& c, int val) {
    auto pos = find_geq( c.begin(), c.end(), val );
    c.insert(pos, val);
}
std::vector<int>::iterator get_position(std::vector<int>::iterator pos, int relative) {
    for(; relative>0; --relative,++pos);
    return pos;
}


class ContainerTest {

    public:
        ContainerTest(int sz, int seed):size(sz), distribution(0,sz-1), generator(seed) {
            for(int i=0; i<size; ++i) {
                values.push_back(100*(i+1));
            }
            for(int i=0; i<size; ++i) {
                int k = size-i-1;
                std::uniform_int_distribution<int> dist{0,k};
                positions.push_back(dist(generator));
                int j = dist(generator);
                int temp = values.at(k);
                values.at(k) = values.at(j);
                values.at(j) = temp;
            }
            std::cerr << "random values:"  << toString(values);
            std::cerr << "random positions:"  << toString(positions);
        }
        int insert() {
            for(int i=0; i<size; ++i){
                insert_ordered( container, values[i]);
                std::cerr << "inserting value "<<values[i]<<":"  << toString( container );
            }
        }
        int remove(){
            for(int i=0; i<size; ++i) {
                auto pos = get_position( container.begin(), positions[i] );
                container.erase(pos);
                std::cerr << "removing position "<< positions[i] <<":" << toString(container);
            }
        }
    private:
        std::vector<int> container;
        std::vector<int> values;
        std::vector<int> positions;
        int size;
        std::uniform_int_distribution<int> distribution;
        std::default_random_engine generator;
};

int main(int argc, char** argv) {
    int size;
    int seed;
    try {
        std::istringstream(argv[1]) >> size;
        std::istringstream(argv[2]) >> seed;
    } catch (...) {
        std::cerr << "usage:\n\t" << argv[0] << " size seed\n";
        return 1;
    }
    StopWatch w;
    ContainerTest t(size, seed);
    w.check();
    t.insert();
    w.check();
    t.remove();
    w.check();
    w.toString(std::cout);
    w.reset();
    return 0;
}
