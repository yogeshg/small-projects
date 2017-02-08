#include<sstream>
#include<iostream>
#include<chrono>
#include<vector>

namespace util {
    template <class Container>
        void toString(Container c, std::ostream& ss) {
            for(auto x: c){
                ss<< x << " ";
            }
            ss<< "\n";
        }
    template <class Container>
        std::string toString (Container c) {
            std::stringstream ss;
            toString(c, ss);
            return ss.str();
        }
    template <class Container>
        void print(Container c) {
            toString(c, std::cout);
        }
}
using namespace std::chrono;
class StopWatch {
    public:
        StopWatch() : t1(system_clock::now()) {
        }
        void check(){
            auto now = system_clock::now();
            d = now-t1;
            check_points.push_back(d.count());
            t1 = now;
        }
        void reset(){
            check();
            check_points.clear();
        }
        void toString(std::ostream& ss) {
            util::toString(check_points, ss);
        }
        std::string toString() {
            return util::toString(check_points);
        }
        std::vector<float> check_points;
    private:
        time_point<system_clock> t1;
        std::chrono::duration<float> d;
};

