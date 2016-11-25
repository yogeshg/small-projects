#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define DBG std::cout << __FILE__ << " " << __LINE__ << " "

class HexLattice {

    int n;
    std::vector<std::vector<std::vector<int>>> val;

    public:
    HexLattice(int num) : n(num) {}

    std::string toString() {
        std::stringstream ss;
        for(auto layer : val) {
            for(auto row : layer) {
                for(auto cell : row) {
                    ss << cell << " ";
                }
                ss << "\n";
            }
            ss << "\n";
        }
        return ss.str();
    }
    void fromCin() {
        int temp;
        for(int i=0; i<n; ++i) {
            std::vector<std::vector<int>> t2;
            val.push_back(t2);
            for(int j=0; j<=i; ++j) {
                std::vector<int> t1;
                val[i].push_back(t1);
                for(int k=0; k<=i-j;++k) {
                    std::cin >> temp;
                    val[i][j].push_back(temp);
                }
            }
        }
    }

};

int main(int argc, char** argv) {
    HexLattice l(3);
    std::cout << l.toString();
    l.fromCin();
    std::cout << l.toString();
    std::cout << "\n";
    return 0;
}
