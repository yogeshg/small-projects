#include<iostream>
#include<vector>
#include<string>
#include<cstring>

class Solution {
    public:

        std::vector<std::vector<std::string>>
            partitionRec(const char* cstr, int len,
                            std::vector<std::string>partSolution ) {
            std::vector<std::vector<std::string>> result;
            if( len<=0 ) {
                result.push_back( partSolution );
                return result;
            }
            std::vector<int> palinCandidates ;
            int palinLen;
            for(palinLen=1; palinLen<=len; ++palinLen) {
                //std::cout<<"trying for len:"<<len<<" palinLen:"<<palinLen;
                bool isPalin = true;
                for( int i=0; i<palinLen/2 && isPalin; ++i ) {
                    isPalin &= cstr[i]==cstr[palinLen-i-1];
                }
                //std::cout<<" isPalin:"<<isPalin<<"\n";
                if(isPalin){
                    palinCandidates.push_back(palinLen);
                }
            }
            for(auto c : palinCandidates) {
                char* buff = new char[c+1];
                std::strncpy(buff, cstr, c);
                buff[c] = '\0';
                partSolution.push_back( buff );
                for(auto sol:partitionRec(cstr+c, len-c, partSolution)) {
                    result.push_back(sol);
                }
                partSolution.pop_back();
            }
            return result;
        }

        std::vector<std::vector<std::string>> partition(std::string s) {
            const int len = s.length();
            std::vector<std::string> partSolution;
            return partitionRec(s.c_str(), len, partSolution);
        }
};

int main(int argc, char** argv) {
    Solution s;
    for( std::vector<std::string> v : s.partition(argv[1]) ) {
        for(std::string st : v) {
            std::cout << st << " ";
        }
        std::cout << "\n"; 
    }
    return 0;
}

