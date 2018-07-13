 
// Link to the task : https://www.codewars.com/kata/sudoku-solution-validator/train/javascript
 
 // Check if the board has 1 or more 0 values
 function checkZero(board) {

    for(var row = 0;row < 9;row++) 
        for(var col = 0; col < 9; col++) 
            if(board[row][col] == 0)
                return true; // It contains 0
    
    return false; // Does not contain 0
    } 
    
    // Check if an element exists in more than once in the row
    // row - the row to check in
    // number - the number that needs to be checks
    function sameLine(board,row,number,colToAvoid) {
    
    // Loop through columns
    for(var col = 0; col < 9; col++)
        if(board[row][col] == number && col != colToAvoid) {
            console.log("linie fals");
            return true; // The number already exists
        }
     
    return false;
    }
    
    // Check if an element exists in more than once in the column
    // column - the row to check in
    // number - the number that needs to be checks
    function sameColumn(board,column,number,rowToAvoid) {
    
    // Loop through columns
    for(var row = 0; row < 9; row++)
    if(board[row][column] == number && row != rowToAvoid) {  
    console.log("col fals",column + " " +row);return true; // The number already exists
    }
    
     
    return false;
    }
    
    
    // Check if a digit is present only once in the box
    function inBox(board,startRow,startCol,number,colToAvoid,rowToAvoid) {
    
    for(var i = 0;i < 3 ; i++) {
        for(var j = 0; j < 3; j++) {
            if(board[i+startRow][j+startCol] == number && j+startCol != colToAvoid && i+startRow !=rowToAvoid ){
                console.log("box fals");
                return true;
            }
                 
        }
    }
    
     
    return false;
    
    }
    
    function validSolution(board){
    
    // If the board is invalid
    if(checkZero(board)) 
        return false;
    
    for(var i = 0;i < 9 ; i++) {
        for(var j = 0; j < 9; j++) {
          if( sameLine(board,i,board[i][j],j)
            || sameColumn(board,j,board[i][j],i)
            || inBox(board,i - i%3,j - j%3, board[i][j],j,i)
          ) return false;
    }
    
    }
    
    return true;
    
    }
     


    // Tests and examples 

    console.log(validSolution([[5, 3, 4, 6, 7, 8, 9, 1, 2], 
                                [6, 7, 2, 1, 9, 5, 3, 4, 8],
                                [1, 9, 8, 3, 4, 2, 5, 6, 7],
                                [8, 5, 9, 7, 6, 1, 4, 2, 3],
                                [4, 2, 6, 8, 5, 3, 7, 9, 1],
                                [7, 1, 3, 9, 2, 4, 8, 5, 6],
                                [9, 6, 1, 5, 3, 7, 2, 8, 4],
                                [2, 8, 7, 4, 1, 9, 6, 3, 5],
                                [3, 4, 5, 2, 8, 6, 1, 7, 9]]));
                                    
    console.log(validSolution([[5, 3, 4, 6, 7, 8, 9, 1, 2], 
                                [6, 7, 2, 1, 9, 0, 3, 4, 8],
                                [1, 0, 0, 3, 4, 2, 5, 6, 0],
                                [8, 5, 9, 7, 6, 1, 0, 2, 0],
                                [4, 2, 6, 8, 5, 3, 7, 9, 1],
                                [7, 1, 3, 9, 2, 4, 8, 5, 6],
                                [9, 0, 1, 5, 3, 7, 2, 1, 4],
                                [2, 8, 7, 4, 1, 9, 6, 3, 5],
                                [3, 0, 0, 4, 8, 1, 1, 7, 9]]));
    
    console.log(validSolution(
        [
            [1, 2, 6, 3, 4, 7, 5, 9, 8],
            [7 ,3, 5, 8, 1, 9, 6, 4, 2],
            [1, 9, 4 ,2 ,7 ,5 ,8 ,6 ,3],
            [3 ,1 ,7, 5 ,8 ,4 ,2 ,6 ,9],
            [7 ,5 ,9 ,1 ,6 ,2 ,4 ,3 ,8],
            [4 ,8 ,2, 9 ,3 ,6, 7 ,1 ,5],
            [1 ,4 ,8 ,7, 5 ,9 ,3 ,2 ,6],
            [5 ,6 ,1, 4, 2, 3, 9 ,8, 7],
            [2 ,7, 3 ,6, 9, 1, ,8 ,5, 4]
        ]
    ));