
namespace yo {
    namespace util {
        void iterable2str(std::vector<int> list, char sep='-') {
            for(auto x = list.begin(); x!=list.end(); ++x) {
                std::cout << *x << sep;
            }
            std::cout << "\n";
            return;
        }
    }
}

// void yo::util::iterable2str(auto list; char sep='-') {
//     for(auto x = list.begin(); x!=list.end(); ++x) {
//         std::cout << *x << sep;
//     }
//     return
// }