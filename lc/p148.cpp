#include<iostream>

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
        ListNode* sortList(ListNode* head) {
            return head;
        }

        static int main(int argc, char** argv ) {
            ListNode* root = NULL;
            for( int i=0; i<10; ++i ) {
                root = prepend( root, i );
            }
            printList(root);
            destroy(root);
            return 0;
        }

};
