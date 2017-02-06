#include<vector>
#include<random>
// #include<chrono>
#include<string>
#include<sstream>
#include<iostream>


void toString(std::vector<int> c, std::ostream& ss) {
    for(auto x: c){
        ss<< x << " ";
    }
    ss<< "\n";
}
std::string toString (std::vector<int> c) {
    std::stringstream ss;
    toString(c, ss);
    return ss.str();
}
void print(std::vector<int> c) {
    toString(c, std::cout);
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
        }
        int insert() {
            for(int i=0; i<size; ++i){
                container.push_back(0);
            }
        }
        int remove(){
            for(int i=0; i<size; ++i) {
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
    try {
        std::istringstream(argv[1]) >> size;
    } catch (...) {
        std::cerr << "usage:\n\t" << argv[0] << " size\n";
        return 1;
    }
    ContainerTest t(size,1991);
    return 0;
}
