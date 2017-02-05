#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n, temp;
    cin >> n;
    long rating[n];
    long candies[n];

    long totalCandies = 0;
    
    for(int i=0; i<n; ++i) {
        cin >> temp;
        rating[i]=temp;
        candies[i] = 1;
    }

    for( int i=1; i<n; ++i) {
        if( rating[i] > rating[i-1] )
            candies[i] = candies[i-1]+1;
    }
    //for(int i=0; i<n; ++i) {
    //    cerr << candies[i] << "\t";
    //}
    //cerr <<"\n";

    for( int i=n-2; i>=0; --i) {
        if( rating[i] > rating[i+1] )
            candies[i] = candies[i+1]+1;
    }
    for(int i=0; i<n; ++i) {
        cerr << "("<<rating[i]<<"@"<<i<<"): "<<candies[i] << "\n";
        totalCandies += candies[i];
    }
    cerr <<"\n";

         
    cout << totalCandies <<"\n";
    return 0;    
}

