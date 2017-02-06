#include<map>
#include<iostream>
#include"util.hpp"

template <class T>
class MapSequence {
public:
    void insert(int i, T val) {
        m.insert(std::pair<int, T>(i, val));
    }
    T at(int i) {
        return m.at(i).second;
    }
    // void erase(int i) {
    //     return m.erase(i);
    // }
private:
    std::map<int, T> m;

};

int main() {

    MapSequence<int> m;
    for(int i = 0; i<1; ++i)
        m.insert( 0, i );

    // print<std::map<int>>( m );

}
