

//1) Print Pascal's Triangle
//2) Print a certain line from Pascal's Triangle

// Specifications : line counting starts at 0

#include <iostream>
using namespace std;

void printPascal(int lines){

    int i,j,c;
    // Number of lines
    for(int line = 1; line <= lines+1; line++) {
        c = 1;
     // Each column of a line
     for(int col = 1; col <=line; col++){
         cout << c << " "; // Every line starts with "1"
        //  Every line is a Binomial Coefficient
         c = c * (line - col) / col;
     }
     cout << "\n";
    }

}

// Print a certain line of the Pascal's Triangle
void printLine(int line){

    // We will use a different method
    
    int * a= new int[40]; // Current line
    int * b= new int[40];// Previous line

    // The peak of the triangle
    a[0] = b[0] = 1;

    for(int i=1; i<=line;i++){
        for(int j=0; j<=i;j++) {
            // Every line starts with 1
            if(j == 0) a[j] =1;
            // Every line ends with 1 
            else if(i == j) a[j] = 1;
            // The remaining elements of the line
            else a[j] = b[j] + b[j-1];
        }
        // Update the previous line
        for(int j =0 ; j <= i; j++){
            b[j] = a[j];
        }
    }

    for(int i =0; i <=line;i++) {
        cout << a[i] << " ";
    }


}

int main() {

    // How many lines 
    int lines = 8;
    printPascal(lines);
    /*
    1 
    1 1 
    1 2 1 
    1 3 3 1 
    1 4 6 4 1 
    1 5 10 10 5 1 
    1 6 15 20 15 6 1 
    1 7 21 35 35 21 7 1 
    1 8 28 56 70 56 28 8 1 
    */
    cout << "\n";

    int lineNumber = 8;
    printLine(lineNumber); // 1 8 28 56 70 56 28 8 1

}