

// Given a linked list, determine the middle element

#include <iostream>
using namespace std;

struct Node {
    int val;
    struct Node * next;
};

struct Node * getLastNode(struct Node * root) {
    struct Node * temp = root;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

void insertNode(struct Node *& first,int val) {
    struct Node * node = new Node();
    node->val = val;
    
    if(!first) {
        first = node;
        first->next = NULL;
    } else {
        struct Node * last = getLastNode(first);
        last->next = node;
        last = node;
        last->next = NULL;
    }
}

int middleElement(struct Node * first) {
    struct Node * fastPointer = first;
    struct Node * slowPointer = first;

    while(fastPointer != NULL) {
        fastPointer = fastPointer->next;
        if(fastPointer != NULL) {
            fastPointer = fastPointer->next;
            slowPointer = slowPointer->next;
        }
    }

    return slowPointer->val;
}

void getInput(struct Node *& first ) {
    int n,val;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> val;
        insertNode(first, val);
    }
}

int main () {
    struct Node * first = NULL;
    getInput(first);
    cout << middleElement(first) << "\n";
}
