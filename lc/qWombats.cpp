#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define DBG std::cerr << __FILE__ << " " << __LINE__ << " "

class HexLattice {

    int n;
    std::vector<std::vector<std::vector<int>>> val;

    public:
    struct Coord {
        int x, y, z;
        Coord() : x(0), y(0), z(0) {};
        Coord(int a, int b, int c) : x(a), y(b), z(c) {};
        void set(int i, int j, int k) {
            x=i; y=j; z=k;
        }
        std::string toString() const{
            char buff[32];
            sprintf(buff, "(%d,%d,%d)", x, y, z);
            return buff;
        }
    };

    HexLattice(int num) : n(num) {
        for(int i=0; i<n; ++i) {
            std::vector<std::vector<int>> t2;
            val.push_back(t2);
            for(int j=0; j<=i; ++j) {
                std::vector<int> t1;
                val[i].push_back(t1);
                for(int k=0; k<=i-j;++k) {
                    val[i][j].push_back(0);
                }
            }
        }
    }

    std::string toString() const{
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
            for(int j=0; j<=i; ++j) {
                for(int k=0; k<=i-j;++k) {
                    std::cin >> temp;
                    val[i][j][k]=temp;
                }
            }
        }
    }

    bool copyItemInto(const Coord& c, int& value) const{
        try {
            value = val.at(c.x).at(c.y).at(c.z);
            return true;
        } catch(const std::out_of_range& oor) {
            return false;
        }
    }

    int& getItem(const Coord& c){
        DBG << "getting item at" << c.toString()<<"\n";
        return val[c.x][c.y][c.z];
    }

    std::vector<Coord> getParents(const Coord& c) {
        std::vector<Coord> r;
        int temp;
        Coord d = c;
        d.x-=1;
        if(copyItemInto(d, temp))
            r.push_back(d);
        d.y-=1;
        if(copyItemInto(d, temp))
            r.push_back(d);
        d.y+=1;
        d.z-=1;
        if(copyItemInto(d, temp))
            r.push_back(d);

        return r;
    }

};

int main(int argc, char** argv) {
    HexLattice l(3);
    std::cout << l.toString();
    l.fromCin();
    std::cout << l.toString();
    HexLattice util(3);
    HexLattice::Coord c;
    for(int i=0; i<3; ++i) {
        for(int j=0; j<=i; ++j) {
            for(int k=0; k<=i-j; ++k) {
                c.set(i,j,k);
                util.getItem(c) = l.getItem(c);
                for( auto p : l.getParents(c)) {
                    util.getItem(c) += util.getItem(p);
                }
                std::cout << util.getItem(c);
                std::cout<<"\t";
            }
            std::cout << "\n";
        }
        std::cout <<"\n";
    }
    std::cout << "\n";
    return 0;
}
