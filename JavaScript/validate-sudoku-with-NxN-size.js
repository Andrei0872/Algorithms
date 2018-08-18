
// Validate Sudoku with size NxN

// Link to the task : https://www.codewars.com/kata/validate-sudoku-with-size-nxn/train/javascript

var Sudoku = function(data) 
{
   
  const N = data.length;
  console.log(N)
  const M = data[0].length;
  console.log(M);

// Check if an element is on a certain line
function sameLine(row,elem,colToAvoid) {
    for(let col =0; col < M;col++) {
        if(data[row][col] === elem && col !== colToAvoid){
            return true;
            console.log(1)
        }
        
    }
    return false;
}

// Check if an element is on a certain column
function sameColumn(col,elem,rowToAvoid)  {
    for(let row = 0; row < N;row++) {
        if(data[row][col] === elem && row !== rowToAvoid ) {
            console.log(1)
            return true;
        }
    }
    return false;
}

// 3x3 Table
function board (startRow,startCol,elem,colToAvoid,rowToAvoid) {
    for(let i = 0; i < Math.floor(Math.sqrt(N));i++) {
        for(let j = 0; j < Math.floor(Math.sqrt(M));j++) {
            //  if(data[i+startRow][j+startCol] > N && data[i+startRow][j+startCol] <= 0) return false;
            if(data[i+startRow][j+startCol] === elem && j+startCol !== colToAvoid && i+startRow !== rowToAvoid ) {
                console.log(i,j,startRow,startCol,elem)
                return true;
            }
        }
    }
    return false;
}

  return {
    isValid: function() {
      if( N !== M) return false;
      if(N==1 && data[0][0] <=0 || data[0][0] !== parseInt(data[0][0],10) || data[0][0] > N) return false;
      
     for(let i=0; i <N;i++) {
         for(let j=0; j<M;j++) {
            //  Out of range or not an integer
             if(data[i][j] !== parseInt(data[i][j]) || data[i][j] <=0 || data[i][j] > N) return false;
             if(board(i - (i % Math.sqrt(N)), j-(j% Math.sqrt(M)),data[i][j],j,i)||
                sameColumn(j,data[i][j],i) ||
                sameLine(i,data[i][j],j)
            )
            return false;
         }
     }

      return true;
    }
  };
};

var goodSudoku1 = new Sudoku([
    [7,8,4, 1,5,9, 3,2,6],
    [5,3,9, 6,7,2, 8,4,1],
    [6,1,2, 4,3,8, 7,5,9],
  
    [9,2,8, 7,1,5, 4,6,3],
    [3,5,7, 8,4,6, 1,9,2],
    [4,6,1, 9,2,3, 5,8,7],
    
    [8,7,6, 3,9,4, 2,1,5],
    [2,4,3, 5,6,1, 9,7,8],
    [1,9,5, 2,8,7, 6,3,4]
  ]);

console.log(goodSudoku1.isValid())