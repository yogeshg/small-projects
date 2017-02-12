#include<set>
#include "util.hpp"


int main(int argc, char** argv){
    std::set<int> values;
    util::print(values);
    values.insert(0);
    util::print(values);
    values.insert(1);
    util::print(values);
    values.insert(4);
    util::print(values);
    values.insert(2);
    util::print(values);

    return 0;
}