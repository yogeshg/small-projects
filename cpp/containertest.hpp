#include<set>
#include<vector>
#include<random>
// #include<iostream>
#include"util.hpp"
#include<algorithm>
using namespace util;

template <class Container>
class ContainerTest {
    typedef typename Container::iterator Iter;
    typedef typename Container::value_type ValueType;
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
    void insert() {
        for(int i=0; i<size; ++i){
#if defined CONTAINER_INSERTS
            container.insert(values[i]);
#else
            insert_ordered( container, values[i]);
#endif
            std::cerr << "inserting value "<<values[i]<<":"  << toString( container );
        }
    }
    void remove(){
        for(int i=0; i<size; ++i) {
            auto pos = get_position( container.begin(), positions[i] );
            container.erase(pos);
            std::cerr << "removing position "<< positions[i] <<":" << toString(container);
        }
    }
    private:
    Container container;
    std::vector<int> values;
    std::vector<int> positions;
    int size;
    std::uniform_int_distribution<int> distribution;
    std::default_random_engine generator;
    static void insert_ordered(Container& c, ValueType val) {
        auto geq_val = [val](ValueType x){return x>val;};
        auto pos = std::find_if(c.begin(), c.end(), geq_val);
        c.insert(pos, val);
    }

    static Iter get_position(Iter pos, int relative) {
        for(; relative>0; --relative,++pos);
        return pos;
    }

};
