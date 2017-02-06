#include<vector>
// #include<random>
// #include<chrono>
#include<string>
#include<sstream>
#include<iostream>

class ContainerTest {

    public:
        ContainerTest(int sz) {
            size = sz;
            for(int i=0; i<size; ++i) {
                positions.push_back(0);
            }

        }
        int generate() {
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
        std::vector<int> positions;
        int size;
};

int main(int argc, char** argv) {
    int size;
    try {
        std::istringstream(argv[1]) >> size;
    } catch (...) {
        std::cerr << "usage:\n\t" << argv[0] << " size\n";
        return 1;
    }
    ContainerTest t(size);
    return 0;
}
