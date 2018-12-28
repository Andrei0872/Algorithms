
// https: //www.codewars.com/kata/tic-tac-toe-checker/train/javascript

/*
-1 - unfinished
1 - X won
2 - O won
0 - draw
*/

function isSolved(board) {
    const len = board.length;
    let row, column, column_mat = [...Array(len)].map(row => [...Array(len)])

    // First diagonal
    if (board[0][0] !== 0 && board.every((row, index, board) => board[index][index] === board[0][0]))
        return ~~board[0][0] // === 1 ? 'X' : 'O';

    // Second diagonal
    if (board[0][len - 1] !== 0 && board.every((row, index, board) => board[index][len - index - 1] === board[0][len - 1]))
        return ~~board[0][len - 1] // === 1 ? 'X' : 'O';

    // Rows
    if ((row = board.find(row => row[0] !== 0 && row.every((item) => item === row[0])))) {
        return row[0] // === 1 ? 'X' : 'O';
    }

    // Columns
    board.forEach((row, index_row) => row.forEach((item, index_col) => column_mat[index_col][index_row] = item))
    if ((column = column_mat.find(row => row[0] !== 0 && row.every((item) => item === row[0]))))
        return column[0] // === 1 ? 'X' : 'O';

    if (board.some(row => row.some(item => item === 0)))
        return -1;

    // Draw
    if (board.every(row => row.every(item => item !== 0)))
        return 0;
}
