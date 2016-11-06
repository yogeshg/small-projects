#include<iostream>
#include<stdlib.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode* n): val(x), next(n) {}
};

void printList( ListNode* list ) {
    if( list ) {
        std::cout << list->val << "->";
        printList( list->next );
    } else {
        std::cout << "|\n";
    }
}

ListNode* prepend(ListNode* list, int x) {
    return new ListNode(x, list);
}

void destroy(ListNode* list) {
    if( list ) {
        ListNode* temp;
        temp = list->next;
        delete list;
        return destroy( temp );
    }
}

class Solution {
    public:
        int level;
        bool debug;
        void levelTab() {
            for( int i = level; i > 0; --i ) {
                std::cout << "  ";
            }
            std::cout << ">";
        }
    public:
        struct SortSolution {
            ListNode* head;
            ListNode* tail;
            SortSolution(ListNode* h, ListNode* t): head(h), tail(t) {}
            SortSolution(): head(NULL), tail(NULL) {}
        };
        SortSolution merge( SortSolution s1, SortSolution s2 ) {
            ListNode* p1;
            ListNode* p2;
            ListNode dummyStart = ListNode(-1);
            ListNode* pCurr = &dummyStart;
            p1 = s1.head;
            p2 = s2.head;
            SortSolution s;
            bool c1, c2;
            if(debug) levelTab();
            if(debug) std::cout << "merging " << s1.head->val <<"-"<<s1.tail->val <<" and " << s2.head->val <<"-"<<s2.tail->val<<"; ";
            if(debug) std::cout << (p1?p1->val:-1) <<" "<< (p2?p2->val:-1) << "; ";
            while( true ) {
                const bool condition = (p1->val <= p2->val);
                pCurr->next = condition ? p1 : p2;
                pCurr = pCurr->next;
                if( condition ) {
                    p1 = p1->next;
                } else {
                    p2 = p2->next;
                }
                c1 = p1==s1.tail->next;
                c2 = p2==s2.tail->next;

                if(c1||c2) {
                    break;
                }
            }
            if(debug) std::cout << (p1?p1->val:-1) <<" "<< (p2?p2->val:-1) << "; ";
            s.head = dummyStart.next;
            if( c1 ) { // p1 hit the tail first
                if(debug) std::cout << "c1; ";
                pCurr->next = p2;
                s.tail = s2.tail;
            } else { // assert c2
                if(debug) std::cout << "c2; ";
                pCurr->next = p1;
                s.tail = s1.tail;
            }
            s.tail->next = NULL;
            if(debug) std::cout<<"into ";
            if(debug) printList(s.head);
            return s;
        }

        SortSolution sort(ListNode* head, int len){
            if(debug) levelTab();
            if(debug) std::cout << "sorting " << head->val << ", " << len <<"\n";
            if(len<=1) {
                return SortSolution(head, head);
            } else {
                int mid = len/2;
                ListNode* head2 = head;
                for( int i = 0; i < mid; ++i ) {
                    // assert head2
                    head2 = head2->next;
                }
                level+=1;
                SortSolution s1 = sort(head, mid);
                SortSolution s2 = sort(head2, len-mid);
                level-=1;
                s1.tail->next = s2.head;
                return merge(s1, s2);
            }
        }
        ListNode* sortList(ListNode* head) {
            int n = 0;
            level=0;
            debug=false; //true;
            ListNode* temp = head;
            while( temp ) {
                temp = temp->next;
                ++n;
            }
            return sort( head, n ).head;
        }

};

int main(int argc, char** argv ) {
    ListNode* root = NULL;
    if(argc >= 3) {
        srandom(atoi(argv[2]));
    }
    for( int i=atoi(argv[1]); i>0; --i ) {
        root = prepend( root, random()%10 );
    }
    printList(root);
    Solution s;
    root = s.sortList( root );
    printList(root);
    destroy(root);
    return 0;
}


