


// https://ideone.com/qq2cII

/**
 * Given a word and a set of words, print all the recommendations to auto-complete the word;
*/

/*
Example
word = and
words[] = {"and","dan","andr","andrei"}
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    struct Node * children[100];
    bool endOfWord;
};

// Create a new node
struct Node * getNode() {
    struct Node *newNode = (struct Node * )malloc(sizeof(struct Node));
    
    newNode->endOfWord = false;
    for(int i = 0; i < 26; i++)
        newNode->children[i] = NULL; 

    return newNode;
}

void addWord(struct Node * root,string word) {
    int character;
    for(int i = 0; i < word.length(); i++) {
        character = word[i] - 'a';
        if(root->children[character] == NULL)
            root->children[character] = getNode();
        root = root->children[character];        
    }
    root->endOfWord = true;
}

void printWords(struct Node * root, string str){
    if(root->endOfWord)
        cout << str << "\n";
    
    for(int i = 0; i < 26; i++) {
        if(root->children[i]) {
            printWords(root->children[i], str + (char)(i + 'a'));
        }
    }
}

void findWords(struct Node * root, string str) {
    string temp = "";
    // Check first any of the word's letters exists
    for(int i = 0; i < str.length(); i++) {
        int ch = str[i] - 'a';
        temp += (str[i]);
        if(root->children[ch] == NULL)
            return;
        // Move to the next letter
        root = root->children[ch];
    }

    printWords(root,temp);
}

int main () {
    int number_of_words, number_of_words_to_find;
    struct Node * root = getNode();

    string str;

    cin >> number_of_words >> number_of_words_to_find; 

    for(int i = 0; i < number_of_words; i++) {
        cin >> str;
        addWord(root,str);
    }

    for(int i = 0; i < number_of_words_to_find; i++) {
        cin >> str;
        findWords(root,str);
    }

    return 0;
}