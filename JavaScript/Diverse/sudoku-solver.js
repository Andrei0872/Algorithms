// https://www.codewars.com/kata/5296bc77afba8baa690002d7/train/javascript


function findEmptyField(puzzle) {
    for (let i = 0; i < 9; i++) {
        for (let j = 0; j < 9; j++) {
            if (puzzle[i][j] === 0) {
                return {
                    i,
                    j
                };
            }
        }
    }
    console.log("ok")
    return {
        i: -1,
        j: -1
    };
}


function sameLine(puzzle, currentRow, number) {
    for (let i = 0; i < puzzle[0].length; i++) {
        if (puzzle[currentRow][i] === number)
            return true;
    }
    return false;
}

function sameColumn(puzzle, currentCol, number) {
    for (let i = 0; i < puzzle.length; i++) {
        if (puzzle[i][currentCol] === number) {
            return true;
        }
    }
    return false;
}


/**
 * Check if a number is already within a box
 * 
 * Box - 3 X 3 matrix
 */
function inBox(puzzle, startRow, startCol, number) {
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            if (puzzle[i + startRow][j + startCol] === number)
                return true;
        }
    }
    return false;
}


function allGood(puzzle, row, col, number) {
    return !sameLine(puzzle, row, number) &&
        !sameColumn(puzzle, col, number) &&
        !inBox(puzzle, row - row % 3, col - col % 3, number);
}


function solution(puzzle) {
    const {
        i,
        j
    } = findEmptyField(puzzle);
    console.log(i, j)
    if (i == -1 || j == -1) return true;


    // console.log(i,j)
    for (let d = 1; d <= 9; d++) {
        if (allGood(puzzle, i, j, d)) {
            puzzle[i][j] = d;
            if (solution(puzzle))
                return true;

            puzzle[i][j] = 0;
        }
    }
    return false;
}


function sudoku(puzzle) {
    if (solution(puzzle)) {
        return puzzle;
    } else return -1;
}




var puzzle = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
];


console.log(sudoku(puzzle));

// Expected 
// [[5,3,4,6,7,8,9,1,2],
// [6,7,2,1,9,5,3,4,8],
// [1,9,8,3,4,2,5,6,7],
// [8,5,9,7,6,1,4,2,3],
// [4,2,6,8,5,3,7,9,1],
// [7,1,3,9,2,4,8,5,6],
// [9,6,1,5,3,7,2,8,4],
// [2,8,7,4,1,9,6,3,5],
// [3,4,5,2,8,6,1,7,9]]