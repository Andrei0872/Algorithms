

/*
        root
    /   \    \
    t   a     b
    |   |     |
    h   n     y
    |   |  \  |
    e   s  y  e
    /  |   |
    i  r   w
    |  |   |
    r  e   e
        |
        r

*/

#include <iostream>
#include <string>
#define ALPHABET_SIZE 26
using namespace std;

struct TrieNode {
    // Every node consists of multiple branches
    TrieNode * children [ALPHABET_SIZE];
    // Mark the end of the word
    bool endOfWord;
};

// Create a new node
struct TrieNode * getNode() {
    struct TrieNode* node = new TrieNode;
    // Initially, there is no word
    node->endOfWord = false;
    // Initialize all its children as being null
    for(int i =0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    // Return the new created node
    return node;
}

void insertNode(struct TrieNode * root, string key) {

    // We basically want to add characters to the root array
    struct TrieNode * p = root; 
    int index;
    for(int i = 0; i < key.length(); i++) {
        index = key[i] - 'a';
        // Create a new node if the key hasn't already been created
        if(!p->children[index])
            // Create a new node, that will also contain an array of other nodes and so on...
            p->children[index] = getNode();
        
        // Switch the branch
        p = p->children[index];
    }
    // Mark the end of word
    p->endOfWord = true;
}

bool search(struct TrieNode * root, string key) {

    int index;
    struct TrieNode * p = root;
    for(int i = 0; i < key.length(); i++) {
        index = key[i] - 'a';
        // If the "branch" has not been initialized
        if(!p->children[index])
            // The key is not present in the dictionary
            return false;
        // Switch to the next branch
        p = p->children[index];
    }

    return (p && p->endOfWord);
}

int main () {

   string keys [] = {"the", "a", "there",
                    "answer", "any", "by",
                     "bye", "their" }; 

    int len = sizeof(keys)/sizeof(keys[0]);

    struct TrieNode * root = getNode();

    // Construct trie
    for(int i =0; i < len; i++) {
        insertNode(root,keys[i]);
    }

    cout << search(root,"the") << "\n"; // 1
    cout << search(root,"their") << "\n"; // 1
    cout << search(root,"there") << "\n"; // 1
    cout << search(root,"these") << "\n"; // 0
    cout << search(root,"answer") << "\n"; // 1 
    
    return 0;
}


