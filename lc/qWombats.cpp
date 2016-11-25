#include <iostream>
#include <string>
#include <sstream>

#define DBG std::cout << __FILE__ << " " << __LINE__ << " "

class HexLattice {

    int n;
    int*** val;

    public:
    HexLattice(int num) {
        DBG << "constructed\n";
        n = num;
        DBG << "\n";
        val = new int**[n];
        for(int i=0; i<n; ++i){
            DBG << "\n";
            val[i] = new int*[i+1];
            for(int j=0; j<=i; ++j) {
                DBG << "\n";
                val[i][j] = new int[j+1];
                for(int k=0; k<=j; ++k) {
                    val[i][j][k] = i+j+k;
                }
            }
        }
    }
    ~HexLattice() {
        DBG << "destructed\n";
        for(int i=0; i<n; ++i){
            for(int j=0; j<=i; ++j) {
                DBG << "\n";
                delete val[i][j];
            }
            DBG << "\n";
            delete val[i];
        }
        DBG << "\n";
        delete val;
    }
    std::string toString() {
        DBG << "tostring\n";
        std::stringstream ss;
        for(int i=0; i<n; ++i) {
            for(int j=0; j<=i; ++j) {
                for(int k=0; k<=j; ++k) {
                    ss << val[i][j][k] <<" ";
                }
                ss << "-\n";
            }
            ss << "----\n";
        }
        return ss.str();
    }
    void fromCin() {
        for(int i=0; i<n; ++i) {
            for(int j=0; j<=i; ++j) {
                for(int k=0; k<=j;++k) {
                    std::cin >> val[i][j][k];
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
