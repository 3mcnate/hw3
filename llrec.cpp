#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{
    // base case: end of list
    if (head == nullptr)
    {   
        smaller = larger = nullptr;
    }
    else {
        // head recursion
        llpivot(head->next, smaller, larger, pivot);
        
        if (head->val <= pivot) push_front(smaller, head);
        else push_front(larger, head);

        head = nullptr;
    }

}

void push_front(Node*& list, Node* node)
{
    node->next = list;
    list = node;
}
