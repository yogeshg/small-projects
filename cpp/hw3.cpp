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
#ifdef CONTAINER
#define XSTR(x) STR(x)
#define STR(x) #x
    std::cout << XSTR(CONTAINER) <<" ";
    ContainerTest<CONTAINER> t(size, seed);
#endif

    w.check();
    t.insert();
    w.check();
    t.remove();
    w.check();
    std::cout << size << " " << seed << " ";
    w.toString(std::cout);
    w.reset();
    return 0;
}
