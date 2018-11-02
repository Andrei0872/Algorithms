

/**
 * Given a matrix of characters and a word, find all occurrences of the given
 * word 
 * A word can be matched in all 8 directions 
 * 
*/

#include <iostream>
#include <string>
#include <sstream>
#define ROW 3
#define COL 5
using namespace std;

// Directions
const int dx[8] = {0,0,-1,1,1,1,-1,-1};
const int dy[8] = {1,-1,0,0,-1,1,1,-1};

// Convert int to string
string to_str(int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}

// Check validity of new coordinates
bool is_valid(int x, int y, int prevX, int prevY) {

    if(x < 0 || y < 0 || x >= ROW || y >= COL || (prevX == x && prevY == y))
        return false;

    return true;
}   


// n - the length of the word
void DFS(char mat[ROW][COL], int row, int col, int prevRow, int prevCol, string word, string path,int index, int n) {

    // A match has not been found
    if(index > n || mat[row][col] != word[index])
        return;

    // Format the string
    path += string(1,word[index]) + "(" +  to_str(row) + ", " + to_str(col) + ") ";

    // Current character matches the last ch in the word    
    if(index == n) {
        cout << path << "\n";
    }

    // Get new coordinates
    int xx, yy;
    for(int d = 0; d < 8;d++) {
        int xx = row + dx[d];
        int yy = col + dy[d];
        if(is_valid(xx,yy,prevRow,prevCol)) {
            DFS(mat,xx,yy,row,col,word,path,index + 1, n);
        }
    }
}

void get_occ(char mat[ROW][COL], string word) {

    int len = word.length();

    for(int i =0; i < ROW; i++)
        for(int j = 0;j < COL; j++) 
            // First letter matters
            if(mat[i][j] == word[0])
                DFS(mat,i,j,-1,-1,word,"",0,len - 1);

}

int main () {
    
     char mat[ROW][COL]= { {'B', 'N', 'E', 'Y', 'S'},
                          {'H', 'E', 'D', 'E', 'S'},
                          {'S', 'G', 'N', 'D', 'E'}
                        };
    string word = "DES";
    get_occ(mat,word);
    return 0;
}

