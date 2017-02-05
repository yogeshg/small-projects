#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

struct ValIdx {
    int val;
    int idx;
    string toString() {
        stringstream ss;
        ss << "(" << val << "@" << idx << ")";
        return ss.str();
    }
};

class MyHeap {
    public:
    MyHeap(const int n, int* b) : N(n), heapLength(n) {
        a = new ValIdx[N];
        for(int i=0; i<N; ++i) {
            a[i].val = b[i];
            a[i].idx = i;
            heapify(i);
            heapLength = i+1;
            cerr << toString();
        }
        // for(int i=N-1; i>=0*(N-1)/2; --i) {
        //     cerr << toString();
        // }
    }
    ~MyHeap() {
        delete a;
    }
    string toString() {
        stringstream ss;
        for(int i=0; i<heapLength; ++i) {
            ss<<a[i].toString()<<"<";
        }
        ss<<"\n";
        return ss.str();
    }
    ValIdx getMin() {
        if(heapLength) {
            --heapLength;
            std::swap(a[0], a[heapLength]);
            bubbleDown(0);
            // cerr << toString();
            return a[heapLength];
        } else {
            ValIdx none;
            none.val=none.idx=-1;
            return none;
        }
    }
    void bubbleDown(int i) {
        const int j = 2*i+1;
        const int k = 2*i+2;
        if( (j) >= heapLength ) {
            return;
        } else {
            // j < heapLength;
            int minidx = j;
            if( (k < heapLength) && (a[k].val<a[j].val) ) {
                minidx = k;
            }
            if( a[minidx].val < a[i].val ) {
                // cerr << minidx << ",";
                std::swap(a[minidx], a[i]);
                bubbleDown(minidx);
            }
        }
    }
    void heapify(int i) {
        if(i) {
            if(a[i].val < a[i/2].val) {
                std::swap(a[i], a[i/2]);
            }
            heapify(i/2);
        }
        return;
    }

    private:
    int N;
    int heapLength;
    ValIdx* a;
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, temp;
    cin >> n;
    int rating[n];
    int candies[n];

    for(int i=0; i<n; ++i) {
        cin >> temp;
        rating[i]=temp;
        candies[i] = 0;
    }

    MyHeap h(n, rating);
    ValIdx currentMin;
    int currentCandies = 0;
    int totalCandies = 0;
    for(int i=0; i<n; ++i) {
        currentMin = h.getMin();
        cerr << currentMin.toString();
        currentCandies = 1;
        if((currentMin.idx>0) && rating[currentMin.idx-1]<rating[currentMin.idx] ) {
            currentCandies = std::max( candies[currentMin.idx-1]+1, currentCandies );
        }
        if((currentMin.idx<n-1) && rating[currentMin.idx+1]<rating[currentMin.idx] ) {
            currentCandies = std::max( candies[currentMin.idx+1]+1, currentCandies );
        }
        candies[currentMin.idx] = currentCandies;
        totalCandies+=currentCandies;
        cerr << ": "<< currentCandies << "\n";
    }
    cout << totalCandies <<"\n";
    return 0;    
}

