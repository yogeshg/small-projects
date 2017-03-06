#include<sstream>
#include<iostream>
#include<vector>

namespace util {

    template<typename T>
    concept bool HasStringFunc = requires(T a){
        { toString(a)} -> std::string;  // has a to_string function which returns a string
         
    };

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


