#include<iostream>
#include<sstream>
#include<cassert>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : 
        val(x), left(NULL), right(NULL) {};
    TreeNode(int x, TreeNode* l, TreeNode* r) :
        val(x), left(l), right(r) {};
};
void destructTreeNode (TreeNode* root) {
    if(!root) return;
    TreeNode* const l = root->left;
    TreeNode* const r = root->right;
    delete root;
    destructTreeNode(l);
    destructTreeNode(r);
}


void treeToCout(TreeNode* root) {
    if( root ) {
        std::cout << "(";
        treeToCout(root->left);
        std::cout << root->val;
        treeToCout(root->right);
        std::cout << ")";
    }
    return;
}

/**
 * level 0 idx: 0
 * level 1 idx: 0 1
 * level 2 idx: 0 1 2 3
 * level 3 idx: 0 1 2 3 4 5 6 7
 * level 4 idx: 0 1 2 3 4 5 6 7 ... 15
 * level 5 idx: 0 1 2 3 4 5 6 7 ... 15 ... 31
 * level 6 idx: 0 1 2 3 4 5 6 7 ... 15 ... 31 ... 63
 * level 7 idx: 0 1 2 3 4 5 6 7 ... 15 ... 31 ...  ... 127
 * level 8 idx: 0 1 2 3 4 5 6 7 ... 15 ... 31 ...  ... 255
 * level 9 idx: 0 1 2 3 4 5 6 7 ... 15 ... 31 ...  ... 511
 * Modifies l and i to refer to the correct level and index in that level
 * Additionally, returns j, where (l,i) refers to the jth node
 */
int normalizeTreeIdx(int& l, int& i) {
    int j = (1<<l)+i;
    assert(j>0);
    for(int temp=j, count=0; temp; temp>>=1) {
        l = count++;
    }
    i = j - (1<<(l));
    return j;
}

TreeNode* getIdx(TreeNode* root, int index, int level=0) {
    normalizeTreeIdx( level, index );
    while( level ) {
        const int levelWidthBy2 = (1<<(level-1));
        const bool inRight = (bool)(index/levelWidthBy2);
        std::cout << level <<","<< index <<","<< levelWidthBy2 <<","<< inRight <<"\n";
        if(inRight) {
            if( !root->right ) {
                root->right = new TreeNode(-1);
            }
            root = root->right;
            index -= levelWidthBy2;
        }
        else {
            if( !root->left ) {
                root->left = new TreeNode(-1);
            }
            root = root->left;
        }
        level -=1;
    }
    return root;
}

TreeNode* makeTree(TreeNode* tree, std::string treeStr, char delim=' ') {
    std::stringstream ss( treeStr );
    std::string nodeStr;
    int idx = 0;
    while(std::getline(ss, nodeStr, delim)) {
        try {
            const auto nodeVal = std::stoi( nodeStr );
            getIdx(tree, idx)->val = nodeVal;
        } catch( std::invalid_argument ) {
        }
        treeToCout( tree );
        std::cout << "\n";
        ++idx;
    }
    return NULL;
}

struct SolutionReturn {
    int soFar;
    int endingHere;
    SolutionReturn() : soFar(0), endingHere(0) {};
};

class Solution {
    public:

        SolutionReturn maxPathSumRec( TreeNode* root ) {
            SolutionReturn s;
            if( !root ) return s;
            SolutionReturn s1 = maxPathSumRec(root->left);
            SolutionReturn s2 = maxPathSumRec(root->right);

            s.endingHere = std::max(s1.endingHere+root->val, s2.endingHere+root->val);
            s.soFar = std::max( std::max(s1.soFar, s2.soFar), s1.endingHere+root->val+s2.endingHere);

            return s;
        }

        int maxPathSum(TreeNode* root) {
            SolutionReturn s = maxPathSumRec( root );
            return s.soFar; 
        }
};

int main(int argc, char** argv) {

    Solution s;
    TreeNode* root = NULL;
    root = new TreeNode(-1);
    treeToCout(root);
    std::cout << "\n";
    // root = new TreeNode(-1);
    for( int i = 0 ; i < argc; ++i ) std::cout << argv[i] <<" ";
    std::cout << "\n";
    makeTree( root, argv[1]);
    treeToCout(root);
    std::cout << "\n";
    std::cout << s.maxPathSum(root) << "\n";
    destructTreeNode(root);
    return 0;
}
