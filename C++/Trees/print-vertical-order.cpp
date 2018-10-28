

//* Print binary tree in vertical order

/*
           1
        /    \ 
       2      3
      / \   /   \
     4   5  6   7
               /  \ 
              8   9 
               
              
Output : 
4
2
1 5 6
3 8
7
9

*/

#include <iostream>
#include <map>
#include <vector>
#include <queue> // Level Order Traversal
using namespace std;

struct Node {
    struct Node * left, *right;
    int data;

    Node(int _data) {
        this->data = _data;
        this->left = this->right = NULL;
    }
};

// Using Recursion
void getVerticalOrder(map<int, vector<int> > & m, int hrDist, struct Node * root) {
    // Base case
    if(!root)
        return;

    // Current distance
    m[hrDist].push_back(root->data);
    getVerticalOrder(m,hrDist-1,root->left);
    getVerticalOrder(m,hrDist+1,root->right);
}

// Using Level Order Traversal
void getVerticalOrder2(map<int, vector<int> > & m, struct Node * root) {
    queue<pair<int, Node*> > q;
    int hrDist = 0,dist;
    vector<int> list;
    Node * node;

    q.push({hrDist,root});

    while(!q.empty()) {
        pair<int, Node*> p = q.front();
        q.pop();
        
        node = p.second;
        dist = p.first;
        list.push_back(node->data);

        m[dist].push_back(node->data);
        if(node->left)
            q.push({dist-1,node->left});
        if(node->right)
            q.push({dist+1,node->right});
    }
}

void printVertical(struct Node * root) {
    map<int, vector<int> > m;

    getVerticalOrder(m,0,root);
    for(auto setOfNodes : m) {
        for(int i = 0; i < setOfNodes.second.size(); i++)
            cout << setOfNodes.second[i] << " ";
        cout << "\n";
    }
    m.clear();
    cout << "\n==========\n\n";

    getVerticalOrder2(m,root);
    for(auto setOfNodes : m) {
        for(int i = 0; i < setOfNodes.second.size(); i++)
            cout << setOfNodes.second[i] << " ";
        cout << "\n";
    }
}

int main () {
    Node * root = new Node(1);
    root->left = new Node(2); 
    root->right = new Node(3); 
    root->left->left = new Node(4); 
    root->left->right = new Node(5); 
    root->right->left = new Node(6); 
    root->right->right = new Node(7); 
    root->right->left->right = new Node(8); 
    root->right->right->right = new Node(9); 

    printVertical(root);
    return 0;
}