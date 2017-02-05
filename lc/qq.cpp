#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Box {
    int l;
    int w;
    Box(const int& x, const int& y) : l(x), w(y) {};
    string toString() {
        std::stringstream ss;
        ss <<"(" << l << "," << w << ")";
        return ss.str();
    }
    //Box(const int& x, const int& y) { 
        // if( x >= y) {
        //    l = x;
        //    w = y;
        //} else {
        //    l = y;
        //    w = x;
        //}
    //};
};

int stackNthBox(const int& n, const std::vector<Box>& boxes,
                std::vector<std::vector<Box>> stacks, int cutoff=INT_MAX ) {
    cutoff=INT_MAX;
    cerr << "stackNthBox " << n << " " << stacks.size() <<" beta="<<cutoff << "\n";
    if( (n >= boxes.size()) )  {
        return stacks.size();
    }
    if( (stacks.size()>cutoff)) {
        return stacks.size()+1;
    }
    int sol_option = INT_MAX;
    int sol_box = INT_MAX;
    const auto curr = boxes[n];
    int id_option = -1;
    int id_best = -1;
    for( auto st : stacks) {
        id_option++;
        const auto stBack = st.back();
        if( (stBack.l > curr.l)&&(stBack.w > curr.w) ) {
            st.push_back(curr);
            sol_option = stackNthBox(n+1, boxes, stacks, sol_box);
            st.pop_back();
            if( sol_option < sol_box) {
                sol_box = sol_option;
                id_best = id_option ;
            }
        }
    }
    id_option++;
    std::vector<Box> new_stack;
    new_stack.push_back(curr);
    stacks.push_back(new_stack);
    sol_option = stackNthBox(n+1, boxes, stacks, sol_box);
    stacks.pop_back();
    new_stack.pop_back();
    
    if( sol_option < sol_box) {
        sol_box = sol_option;
        id_best = id_option ;
        std::cerr << "best at last";
    }
    std::cerr << "best: " << sol_box << "\n";
    return sol_box;
}

int stackboxes(const int& N, const std::vector<Box>& boxes) {
    vector<vector<Box>> stacks;
    const int result = stackNthBox(0, boxes, stacks);
    // std::cerr <<"\n" << result << "\n";
    std::cout << result << "\n";
    return result;
}  

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N, x, y;
    std::vector<Box> boxes;
    std::cin >> N;
    for(int i=0; i<N; ++i) {
        std::cin >> x >> y;
        Box b(x, y);
        boxes.push_back(b);
        // w.push_back(temp2);
    }
    //     // sort using a lambda expression 
    // std::sort(s.begin(), s.end(), [](int a, int b) {
    //    return b < a;   
    // });
    //for(auto b:boxes) {
    //    std::cerr << b.toString() << "\n";
    //}
    std::sort(boxes.begin(), boxes.end(), [](Box a, Box b) {return b.w < a.w;});
    std::sort(boxes.begin(), boxes.end(), [](Box a, Box b) {return b.l < a.l;});
    for(auto b:boxes) {
        std::cerr << b.toString() << "\n";
    }
    return stackboxes(N,boxes);
}
