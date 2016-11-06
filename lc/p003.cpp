class AlphabetRecord {
public:
    uint32_t size;
    int32_t* mAlphabet;
    AlphabetRecord() {
        size = sizeof(char);
        mAlphabet = new int32_t[size];
        for(int i=0; i<size; ++i) {
            mAlphabet[i] = -1;
        }
    }
    ~AlphabetRecord() {
        delete mAlphabet;
    }
    void record(char c, int32_t i) {
        mAlphabet[c]=i;
    }
    int32_t get(char c) {
        return mAlphabet[c];
    }
    void resetUntil(int32_t j) {
        for(int i = 0; i < size; ++i) {
            if( mAlphabet[i] <= j ) {
                mAlphabet[i] = -1;
            }
        }
    }
};

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        uint32_t N = s.length();
        uint32_t longestSoFar = 0;
        uint32_t longestEndingHere[N];
        int32_t j;
        char c;
        AlphabetRecord rec;
        if( N ) {
            longestSoFar = 1;
            rec.record(s[0], 0);
        }
        for(int i=0; i<N; ++i) {
            c = s[i];
            j = rec.get(c);
            if(j<0) {
                longestEndingHere[i] = longestEndingHere[i-1]+1;
            } else {
                rec.resetUntil(j);
                longestEndingHere[i] = i-j;
            }
            rec.record(c, i);
            longestSoFar = max(longestSoFar, longestEndingHere[i]);
        }
        return longestSoFar;
    }
};


/*

class AlphabetRecord {
public:
    uint32_t size;
    int32_t* mIndex;
    int32_t* mLastChar;
    char lastChar;
    AlphabetRecord() {
        size = sizeof(char);
        mIndex = new int32_t[size];
        mLastChar = new int32_t[size];
        lastChar = -1;
        for(int i=0; i<size; ++i) {
            mIndex[i] = -1;
            mLastChar[i] = -1;
        }
    }
    ~AlphabetRecord() {
        delete mIndex;
        delete mLastChar;
    }
    void record(char c, int32_t i) {
        mIndex[c]=i;
        mLastChar[c] = lastChar;
        lastChar = c;
    }
    int32_t get(char c) {
        return mIndex[c];
    }
    void resetBefore(int32_t c) {
        int32_t d;
        if( c >= 0 ) {
            mIndex[c] = -1;
            d = mLastChar[c];
            mLastChar[c] = -1;
            resetBefore(d);
        }
    }
    void resetUntil2(int32_t j) {
        for(int i = 0; i < size; ++i) {
            if( mIndex[i] <= j ) {
                mIndex[i] = -1;
            }
        }
    }
    
};

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        uint32_t N = s.length();
        uint32_t longestSoFar = 0;
        uint32_t longestEndingHere[N];
        int32_t j;
        char c;
        AlphabetRecord rec;
        if( N ) {
            longestSoFar = 1;
            rec.record(s[0], 0);
        }
        std::cout << "hello\n";
        for(int i=0; i<N; ++i) {
            c = s[i];
            j = rec.get(c);
            std::cout << i << "\t" <<j<< "\t" << c;
            if(j<0) {
                longestEndingHere[i] = longestEndingHere[i-1]+1;
            } else {
                rec.resetBefore( c );
                longestEndingHere[i] = i-j;
            }
            rec.record(c, i);
            longestSoFar = max(longestSoFar, longestEndingHere[i]);
            std::cout <<"\t"<< longestEndingHere[i] <<"\t"<< longestSoFar << "\n";
        }
        return longestSoFar;
    }
};

 */