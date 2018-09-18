

/**
 * Find a word in a matrix of characters
 * A word can be matched in all 8 directions at any point
*/

/*
Example :
grid =  {"GEEANDREIEEKS",
        "BQEKSQUTZGEVB",
        "IGRQAXRZCTIKE"
        };
Word = ANDREI
Output = Found at 0 3
Word = IQE
*/

#include <iostream>
#include <cstring>
using namespace std;

int R = 3, C = 14;

// Directions
const int dx[8] = {0,0,-1,1,1,1,-1,-1};
const int dy[8] = {1,-1,0,0,-1,1,1,-1};

// Check if 2 coordinates are valid

bool word_found(char grid[][14],int row, int col,const char * word) {
    
    // Check the first letter of the word 
    if(grid[row][col] != word[0])
        return false;

    int len = strlen(word);
    int new_x, new_y,letter;
    for(int dir = 0; dir < 8; dir++) {
        // Get the new coordinates
        new_x = row + dx[dir];
        new_y = col + dy[dir];
        
        // Check with word's letters    
        for(letter = 1; letter < len ;letter++) {
            if(word[letter] != grid[new_x][new_y])
                break;
            
            // Check if the coordinates are valid
            if(new_x < 0 || new_x >= R || new_y < 0 || new_y >= C )
                break; // Keep searching

            // If there is a match, upgrade the coordinates
            new_x += dx[dir];
            new_y += dy[dir];
        }
        // If we found a match
        if(letter == len )
            return true;
    }

    // No match found
    return false;
}

void findWord(char grid[][14],const char * word) {

    // Take each cells as a starting point
    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++)
            if(word_found(grid,i,j,word)) 
                cout << "Found at : " << i << " " << j << "\n";

}

int main () {
    char grid[3][14] = {"GEEANDREIEEKS",
                    "BQEKSQUTZGEVB",
                    "IGRQAXRZCTIKE"
                    };
    const char * word = "ANDREI";
    findWord(grid,word); // 0 3
    cout << "\n";
    const char * word2 = "IQE"; // 2 0
    findWord(grid,word2);
}

