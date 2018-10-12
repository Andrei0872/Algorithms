
// Given an array of strings, print them in alphabetical order

/*
words [] = {"abc", "xy", "bcd"};
Output : abc bcd xy
*/

#include <iostream>
#include <string>
#define ALPHABET 26
using namespace std;

struct Trie {
    int index;
    struct Trie * children[ALPHABET];
    
    Trie () {
        for(int i = 0; i < ALPHABET; i++)
            children[i] = NULL;
        index = -1;
    }
};

void addWord(struct Trie * root, string word, int index) {
    int ch;
    
    for(int i = 0; i < word.length(); i++) {
        ch = word[i] - 'a';
        if(!root->children[ch]) 
            root->children[ch] = new Trie();
        root = root->children[ch];
    }
    
    root->index = index;
}

void sort_words(struct Trie * root, string words[]) {
    // Base case
    if(!root)
        return;

    for(int i = 0; i < ALPHABET; i++) {
        // If there is a word that contains the current letter
        if(root->children[i] != NULL) {
            if(root->children[i]->index != -1 )
                cout << words[root->children[i]->index] << " ";
            
            sort_words(root->children[i],words);
        }   
    }
}

void solve(string words[], int len) {
    struct Trie * root = new Trie();
    
    for(int i = 0; i < len; i++)
        addWord(root,words[i],i);
    
    sort_words(root,words);
}

int main () {
    string words[] = {"andrei","computer","pen","book","programmer"};
    int len = sizeof(words) / sizeof(words[0]);

    solve(words,len);
    return 0;
}