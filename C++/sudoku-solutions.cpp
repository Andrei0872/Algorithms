
/*
   
   Example : 
   
   Given Matrix : 
   
      {{5, 1, 6, 3, 0, 8, 4, 0, 0},
      {3, 2, 0, 0, 0, 0, 0, 0, 0},
      {0, 8, 7, 0, 0, 0, 0, 3, 1},
      {0, 0, 3, 0, 1, 0, 0, 8, 0},
      {9, 0, 0, 8, 6, 3, 0, 0, 5},       
      {0, 5, 0, 0, 9, 0, 6, 0, 0},
      {1, 3, 0, 0, 0, 0, 2, 5, 0},
      {0, 0, 0, 0, 0, 0, 0, 7, 4},
      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
      
  Result : 
  
      5 1 6 3 7 8 4 9 2 
      3 2 9 1 5 4 7 6 8 
      4 8 7 6 2 9 5 3 1 
      2 6 3 4 1 5 9 8 7 
      9 7 4 8 6 3 1 2 5 
      8 5 1 7 9 2 6 4 3 
      1 3 8 9 4 7 2 5 6 
      6 9 2 5 3 1 8 7 4 
      7 4 5 2 8 6 3 1 9     
   
   
*/

/*
 Reasoning : {
   1) Find an empty field, then, using its coordinates, find if a digit can be assigned to this field 
   
   2) In order to fill a field, a digit must : not be already present in the line/column/box(3 x 3 )
   
   3) Once filled, search for another correct values, but we also have to make sure that we have a way back, just in case something goes wrong
 }
*/


#include <iostream>
using namespace std;

 

// Check if there is any empty field
bool existsEmpty(int mat[9][9], int &row, int &col) {

   // Loop through the matrix and see if there is any empty field (0)
   for(row = 0; row < 9; row ++) 
      for(col = 0; col < 9; col++)
         if(mat[row][col] == 0) 
            return true; // We found an empty field         
   

   // Well, if there is no empty field..
    return false;

}

// Check if the number is present or not in the current row
// currentRow - the row that we need to check
// number - the value that will be checked
bool sameLine(int mat[9][9], int currentRow,int number) {
   
   // Loop through columns
   // j - the column
   for(int j =0; j < 9;j++) 
      if(mat[currentRow][j] == number)
         return true; // The number is already present in this row
   

   return false; // The number is not present

}

// Check if the number is present or not in the current column
// currentCol - the column that we need to check
// number - the value that will be checked
bool sameColumn(int mat[9][9], int currentCol, int number) {

   // Loop through rows
   for(int i = 0; i < 9;i++) 
      if(mat[i][currentCol] == number) 
         return true; // The number is already present in this column
   

   return false; // The number is not present

}

// Remember that the number must not be present more than once in its box (3 x 3)
// Check if the number is not present anywhere else in the current box
bool inBox(int mat[9][9], int startRow, int startCol,int number) {
      
     // The size of box must be 3 x 3 
     for(int i=0; i < 3; i++) {
      for(int j=0; j < 3; j++) {
           if(mat[i+startRow][j+startCol] == number) // If the number is already in the box
            return true;
         }
     } 

   // If the number has not been found
   return false;
   
}



// If the number matches all the conditions..
bool allGood(int mat[9][9],int row, int col, int number) {
   
   if(!sameLine(mat,row,number) // If it is not already present in the line
      && !sameColumn(mat,col,number) // If it is not already present in the column
      // row-row%3 and col-col%3 - in order to get the current box
      && !inBox(mat, row - row%3,col-col%3,number) //If the numbers isn't already in the box
   ) return true;   
      
      
     return false; 
}


// The function that implements Backtracking
bool solution(int mat[9][9]) {
 
   int row,col;
   
   // Check first if there is any available field
   // Here we will also assign values to row and col, since we pass them by reference
   if(!existsEmpty(mat,row,col)) // If there is nothing left to fill.. 
      return true;   // It ends here
   
      // Loop through the matrix and fill the empty fields correctly
      // Remember that we can only insert numbers from 1 to 9
      for(int i=1;i<=9;i++) {
         
         // Check if the number can fill the empty field
         if(allGood(mat,row,col,i)){
         
         // Assign the value, then check if this value matches the conditions
         mat[row][col] = i;
         
            // Use backtracking
            if(solution(mat)) 
            return true; // And now looks for the next element and so on..
         
         // Make sure we get all the possible cases, by remaking the field empty
         mat[row][col] = 0;
         
         }
      }
   
   // To make sure the backtracking works
   return false; // Because if it returns false, we are able to search for multiple solutions starting from a certain field 
   /*
     example:
     
     X - the field we are at now
     0 - empty fields
     1 - filled fields
     
           ^ -> let's say we go for this filed, and keeps on going well(the next fields match all conditions), but, at a certain point, the next element doesn't match the conditions; Then, it returns false, and so we can make use of this statement : mat[row][col] = 0;
           |
           |
       1 0 0 
       0 X 1
       1 1 0
   */
   
}




// Print what we have
void printSudoku(int mat[9][9]) {
   
   
    for (int i = 0; i < 9; i++){
       
          for (int j = 0; j < 9;j++)   
               cout << mat[i][j] << " ";
           cout << endl;
       }
}

int main () {

   // The given matrix
   int mat[9][9] = {{5, 1, 6, 3, 0, 8, 4, 0, 0},
                      {3, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
   
   if(solution(mat) == true) {
      printSudoku(mat);
  } else 
         cout << "there is no solution";
         return 0;
}
