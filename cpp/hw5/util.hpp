#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include<sstream>
#include<iostream>
#include<vector>

namespace util {

    template<typename T>
    concept bool HasStringFunc = requires(T a){
        {toString(a)} -> std::string;
    };

    // template<typename C, typename V, typename I>
    // concept bool Container = requires(C c) {
    //     {c.begin()} -> I;
    //     {c.end()} -> I;
    // }

    template <class Container>
        void toString(Container c, std::ostream& ss) {
            for(auto x=c.begin(); x!=c.end(); ++x) {
            // for(auto x: c){}
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

}


#endif /*__UTIL_HPP__*/