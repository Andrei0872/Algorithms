


// Find all possible words in a board of characters

/*
Example 
Input: 
    string dict [] = {"ANDREI", "ADZ", "AER", "ABC","ZEU"};   
    char matrix [M][N] =  {{'A','N','Z'},
                          {'U','E','D'},
                          {'I','E','R'}
                             };


Output:  Following words of dictionary are present
         AER
         ANDREI
         ZEU
*/


#include <iostream>
#include <string>
#include <set> // Avoid duplicates
#include <algorithm>
#define ALPHABET_SIZE 26
#define N 3
#define M 3
// Convert character into corresponding index
#define char_int(c) ((int)c - (int)'A')
using namespace std;

// Directions
const int dx [8] = {0,0,-1,1,1,-1,1,-1};
const int dy [8] = {-1,1,0,0,1,-1,-1,1};

struct TrieNode {
    TrieNode * children[ALPHABET_SIZE];
    bool endOfWord;
};

struct TrieNode * getNode() {
    struct TrieNode * node = new TrieNode;
    node->endOfWord = false;
    for(int i =0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    return node; 
}

void insert(struct TrieNode * root, string key) {

    int index;
    struct TrieNode * p = root;
    for(int i = 0; i < key.length(); i++) {
        index = char_int(key[i]);

        if(!p->children[index])
            p->children[index] = getNode();
        // Switch the branch
        p = p->children[index];
    }
    p->endOfWord = true;
}

// Check the validity of 2 coordinates
bool isSafe(int i, int j, bool visited [M][N]) {
    if(i < 0 || j < 0 || i >= M || j >= N || visited[i][j])
        return false;
    
    return true;
}

void search(struct TrieNode * root,char matrix[M][N] ,bool visited[M][N], int i, int j, string str, set<string> &strings_found) {

    // If we reached the end of the word
    if(root->endOfWord)
        strings_found.insert(str);

    char ch;
    int xx,yy;
    // Check the positions' validity
    if(isSafe(i,j,visited)) {

        visited[i][j] = true;

        // cout << "safe " << i << " " << j << "\n";
        for(int letter = 0; letter < ALPHABET_SIZE; letter++) {
            if(root->children[letter]) {
                ch = (char)letter + (char)'A';
                // Check all 8 directions
                for(int d = 0; d < 8; d++) {
                    // Get the new coordinates
                    xx = i + dx[d];
                    yy = j + dy[d];
                    if(isSafe(xx,yy,visited) && matrix[xx][yy] == ch) {
                        search(root->children[letter],matrix,visited,xx,yy,str + ch,strings_found);
                    }
                }
            }
        }
        
        visited[i][j] = false;
    }
}

void findWord(char mat[M][N], struct TrieNode * root) {

    bool visited[M][N];
    fill(visited[0], visited[0] + M * N, false);
    string str = "";
    struct TrieNode * p = root;
    char current_letter;
    set<string> strings_found;    
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            
            current_letter = mat[i][j];
            // If the letter has already been defined in the Trie
            
            if(p->children[char_int(mat[i][j])]) {
                // Start creating the string
                str += current_letter;
                // Pass the switched branch
                search(p->children[char_int(mat[i][j])],mat,visited, i, j, str,strings_found);
                str = "";
            
            }            
        
        }
    }

    // Print found strings
    for(auto str : strings_found)
        cout << str << "\n";

}

int main () {

    string dict [] = {"ANDREI", "ADZ", "AER", "ABC","ZEU"};   
    int len = sizeof(dict)/sizeof(dict[0]);
    char matrix [M][N] =  {{'A','N','Z'},
                          {'U','E','D'},
                          {'I','E','R'}
                        };

    struct TrieNode * root = getNode();
    // Construct trie
    for(int i = 0; i < len; i++)
        insert(root,dict[i]);        

    findWord(matrix,root); // AER, ANDREI, ZEU
    
    return 0;
}



