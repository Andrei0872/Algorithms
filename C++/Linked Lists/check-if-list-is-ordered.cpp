
// Given a linked list, check whether the items are in ascending order or not

#include <iostream>
using namespace std;

struct Node {
    int val;
    struct Node * next;

    Node(int _val) {
        this->val = _val;
    }
};

struct Node * getLast(Node * first) {
    Node * p = first;

    while(p->next) {
        p = p -> next;
    }

    return p;
}

struct Node * add(Node * root, int val) {
    if(!root) {
        root = new Node(val);
        root->next = NULL;
        return root;
    }
    Node * last = getLast(root);
    Node * newNode = new Node(val);
    last->next = newNode;
    last = newNode;
    last->next = NULL;
    
    return root;
}

void printList(struct Node * first) {
    Node * temp = first;

    while(temp) {
        cout << temp->val << " ";
        temp = temp->next;
    }

    cout << '\n';
}


bool ascOrder(struct Node * first) {
    struct Node * temp = first;
    int prev = temp->val;
    temp = temp->next;
    
    while(temp) {
        int currentVal = temp->val;
        if(prev > currentVal) return false;
        prev = currentVal;
        temp = temp->next;
    }

    return true;
}

int main () {
    struct Node * root = NULL;

    root = add(root, 3);
    root = add(root, 4);
    root = add(root, 5);
    root = add(root, 10);
    root = add(root, 11);

    printList(root);

    cout << ascOrder(root); 

    return 0;
}
