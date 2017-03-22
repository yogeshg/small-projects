#include<vector>
#include<list>
#include"containertest.hpp"

template <int sz>
struct Big {
    int a;
    int arr[sz-1];
    Big(const int& v): a(v) {}
    friend bool operator> (const Big<sz>& lhs, const Big<sz>& rhs) {
        return lhs.a>rhs.a;
    }
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

    ContainerTest<std::vector<int>> t(size, seed);
    t.run(w);
    std::cout << size << " " << seed << " ";
    w.toString(std::cout);
    w.reset();

    ContainerTest<std::list<int>> t2(size, seed);
    t2.run(w);
    std::cout << size << " " << seed << " ";
    w.toString(std::cout);
    w.reset();

    return 0;
}
