
#include<iostream>
#include<string>
#include<sstream>

class Temp {
    int r;
    int i;
  public:
    Temp(int a, int b): r(a), i(b) {};
    Temp(): r(0), i(0) {};
    std::string toString() {
        std::stringstream ss;
        ss << r << "+i" << i;
        return ss.str();
    }
};

int main() {
  Temp t{1,2};
  std::cout << "Hello World\n" << t.toString() << "\n";
}
