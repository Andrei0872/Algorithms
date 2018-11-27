// https://www.codewars.com/kata/59c5d0b0a25c8c99ca000237/train/javascript

//* Life safari - Is that a line ?

function line(grid) {

    const is_included = (test, existing) => existing.includes(test);
    const directions = [
        [-1,0],[0,1],
        [1,0],[0,-1]
    ]; 
    let g; // The grid that will be modified

    let traverse = ([x,y], dir) => {
        // Mark as 'visited'
        g[x][y] = ' ';
        let neighbors = directions.map(([X,Y]) => [X + x, Y + y]);
        let valid_dir = neighbors.map(([R, C]) => g[R] && g[R][C] || ' ').map((d, i) => d != '-|-|' [i] ? d : ' ')
        let [U, R, D, L] = valid_dir;
        
        let go = d => traverse(neighbors['URDL'.indexOf(d)], d);

        switch(grid[x][y]) {
            case 'X':
                return dir && g.every(row => row.every(item => item === ' ')) 
                    ||
                    (valid_dir.join``.match(/\S/g) || []).length === 1 && go('URDL'[valid_dir.findIndex(d => d !== ' ')])
            case '-':
                return is_included(dir, 'RL') && go(dir)
            case '|':
                return is_included(dir, 'UD') && go(dir)
            case '+':
                // Do we have to move horizontally from vertically or viceversa
                return is_included(dir, 'RL') ? 
                    (is_included(D, '- ') && is_included(U, '|+X') && go('U')) || (is_included(U, '- ') && is_included(D, '|+X') && go('D')) // Hr to V
                    :
                    (is_included(R, '| ') && is_included(L, '-+X') && go('L') )|| (is_included(L, '| ') && is_included(R, '-+X') && go('R')) // V to Hr

        }
        return false;
    }
    
    return grid.some((row, index_row) => [...row].some((item, index_col) => item === 'X' && (g = grid.map(row => [...row]), traverse([index_row, index_col]))))
}


// console.log(line([
//     " ",
//     " +-------+ ",
//     " | +++---+ ",
//     "X--+ +-+ X "
// ]))

console.log(line([
    "                    ",    
    "     +--------+     ",
    "  X--+        +--+  ",
    "                 |  ",
    "                 X  ",
    "                    "
    ]))

console.log(line(["X-----|----X"]))

console.log(line([
    " X  ",
    " |  ",
    " +  ",
    " X  "
]))