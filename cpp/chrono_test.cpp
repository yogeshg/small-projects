#include<iostream>
#include<chrono>
#include<sstream>
#include<iomanip>

using namespace std::chrono;

int main(int argc, char** argv) {
    time_point<system_clock> t1;
    time_point<system_clock> t2;
    t1 = system_clock::now();
    int64_t s=0;
    for(int i=0;i<100000;++i){
        s+=i;
    }
    t2 = system_clock::now();
    system_clock::duration d = t2-t1;
    std::cout << duration_cast<nanoseconds>(d).count() << "nanoseconds\n";

    std::cout << "Hello World\n";
    return 0;
}
