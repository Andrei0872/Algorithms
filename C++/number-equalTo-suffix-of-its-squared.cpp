
/*
* Given a matrix, determine the index of the row that contains 
* the most numbers which are equal to one suffix of their squared
* 
* Example of a valid number {
* 1) 25 is a valid number, because 25 ^ 2 = 625
}
*
* Example of Input/Output {
*     
* 1)   
* n = 3   
* mat = 2 5 8  - 5  
*       3 5 25 - 5, 25
*       6 4 4  - 6    
*
* Output : 2 - Second row
}
*
*/

#include <iostream>
using namespace std;

int n;

bool isValid(int x ) {

    // Get the squared number
    int squared = x * x;

    while( x > 0) {
        // Check their last digits
        if(x % 10 != squared % 10)
            return false;
        x /= 10;
        squared /= 10;
    }

    // If we got this far, the number is valid
    return true;
}

int getRowIndex(int **mat,int n) {
    int rowIndex,
        maxValid = 0;
    
    for(int i =0; i < n;i++) {
        int maxRow = 0;
        for(int j =0 ; j < n; j++) {
            if(isValid(mat[i][j])) 
                maxRow++;
        }
        // Determine the row index
        if(maxRow > maxValid ) {
            maxValid = maxRow;
            rowIndex = i;
        }
    }

    return rowIndex + 1;
} 

int main () {

    cin >> n;

    int **mat = new int *[n];

    // Get user input
    for(int i=0; i < n; i++) {
        mat[i] = new int[n];
        for(int j =0; j < n; j++) {
            cin >> mat[i][j];
        }
    }


    cout << getRowIndex(mat,n) << "\n";

    return 0;

}
