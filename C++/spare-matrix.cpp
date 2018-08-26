



/**
 * Given 2 sparse matrixes represented as one dimensional arrays, print their sum as a matrix
 * 
 * -1-1-1 - Breakpoint 
 * 
 * Example : {
 *  n = m = 3
 * Matrix A
 * 2 2 2 
 * 3 3 3
 * 1 2 5
 * 3 1 2
 * 1 3 5
 * -1-1-1
 * Matrix B
 * 3 2 4
 * 1 2 -5
 * 2 2 1
 * -1-1-1 
 * 
 * }
 * 
 * 
 * 
*/

#include <iostream>
using namespace std;

struct triplet {
    int row,
        col,
        val;
    triplet * next;
};

triplet * getLastNode(triplet * start) {
    triplet * temp = start;
    while(temp->next) temp = temp->next;
    return temp;
}

triplet *  add(triplet * start,int row, int col, int val) {

    // Create new node
    triplet * new_node = new triplet;

    new_node->row = row;
    new_node->col = col;
    new_node->val = val;

    // If the list has not been created yet
    if(!start) {
        start = new_node;
        start->next = NULL;
        return start;
    } else {
        // If the list has been created, get the last node and make the connection
       triplet *last = getLastNode(start);
       last->next = new_node;
       last = new_node;
       last ->next = NULL;
    }  

}


void printList(triplet * st) {
    triplet *temp = st;
    for(;temp;temp=temp->next) {
        cout << temp->row << " ";
        cout << temp->col << " ";
        cout << temp->val << " ";
        cout << "\n";
    }
}

void getInput(triplet **start1,triplet **start2, int &n, int &m) {
    // Dimensions of the matrix 
    cin >> n >> m;

    // When the next triplet is encounterd : -1-1-1
    // It means we're going to get the input from the second matrix
    int breakpoits = 0;
    int col,row,val;

    while(1) {

        if(breakpoits == 2) {
            break;
        }
        cin >> row >> col >> val;

        // Breakpoint encountered
        if(row == col && col == val && val == -1) {
            breakpoits++; continue;
        }

        // Deferencing the pointer that points to this pointer... I know how it sounds!
        // *start = add(*start,etc..)

        // Determine for which matrix we are getting input
        if(breakpoits == 0) {
            // First sparse matrix
            if(!*start1) {
                // The list has not been created yet
                *start1 = add(*start1,row,col,val);
            }
            else add(*start1,row,col,val);

        }else if(breakpoits == 1) {
            // Second sparse matrix
            if(!*start2) {
                // The list has not been created yet
                *start2 = add(*start2,row,col,val);
            }
            else add(*start2,row,col,val);
        }

    }
}

// Check if a list has a certain column and row
int searchInList(triplet * start, int row, int col) {

    triplet *temp = start;
    while(temp) {
        if(temp->row == row && temp->col == col)
            return temp->val;
        // Keep searching
        temp = temp->next;
    }

    // Row & Column have not been found
    return 0;
}

void solve() {

    triplet *start1=NULL, *start2 = NULL;
    int n,m;
    // getInput(**startPointer1,**startPointer2) : **startPointer holds the address of start
    getInput(&start1,&start2,n,m);

    // Final sparse matrix containing the sum of the other 2 sparse matrix
    int **finalMatrix = new int *[n]; // Rows
    for(int i =0;i < n;i++) {
        // Create a new row
        finalMatrix[i] = new int[m]; // Number of columns
        for(int j=0; j < m; j++) {

            // If a row & col have not been found in any of the 2 lists
            // c[row][col] = 0

            // Search for row and col 
            int value_from_first = searchInList(start1,i+1,j+1);
            int value_from_second = searchInList(start2,i+1,j+1);
            finalMatrix[i][j] =  value_from_first + value_from_second;
        }
    }

    // Print the matrix 
    for(int i =0 ;i < n; i++) {
        for(int j =0; j < m;j++){
            cout << finalMatrix[i][j] << " ";
        }
        cout << "\n";
    }
    delete finalMatrix;
}


int main () {

    solve();

    return 0;
    
}