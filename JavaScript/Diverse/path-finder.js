

// https://www.codewars.com/kata/57658bfa28ed87ecfa00058a/train/javascript

//* Path finder

// . - empty space
// W - Wall 
function pathFinder(maze){
    const dx = [-1,1,0,0];
    const dy = [0,0,-1,1];
    
    let correct_maze = maze.replace(/\s/g,'');
    let len = Math.sqrt(correct_maze.length)
    let regex = new RegExp(`[W|\.]{1,${len}}`,'g');
    let split_maze = correct_maze.match(regex)    
    let initial_matrix = [...Array(len)].map((item, index) => [...split_maze[index]])
    let lee = Array.from({length : len}, item => [...Array(len)].fill(0));

    let queue = [];

    // Starting position
    queue.push({row:0,col:0});
    lee[0][0] = 1;

    while(queue.length !== 0) {
        let coordinates = queue[0];
        queue.shift();
        let row = coordinates.row;
        let col = coordinates.col;

        for(let d = 0; d < 4 ; d++) {
            let new_row = row + dx[d];
            let new_col = col + dy[d];
            
            if(valid_coordinates(new_row,new_col)) {
                lee[new_row][new_col] = lee[row][col] + 1;
                queue.push({row:new_row, col:new_col});
            }
        }
    }

    function valid_coordinates(x,y) {
        if (x < 0 || y < 0 || x >= len || y >= len || lee[x][y] !== 0 ||  initial_matrix[x][y] === 'W' )
            return false;
        return true;
    }

    return lee[len-1][len-1] !== 0 ? lee[len-1][len-1] - 1 : false;
}

console.log(pathFinder(
`.W.
.W.
...`)) // 4


console.log(pathFinder(
`......
......
......
......
.....W
....W.`)) // false


console.log(pathFinder(`......
......
......
......
......
......`)) // 10

// ==================================================

function pathFinder2(maze) {
    const matrix = maze.split`\n`.map(row => row.split``);
    console.log(matrix)
    
    const queue = [{x: 0, y: 0, len: 0}];
    const n = matrix.length - 1;

    while(queue.length) {
        const {x, y, len} = queue.shift();
        if(x == n && y == n) 
            return len;
        
        // Mark this as visited
        matrix[x][y] = 'W';
        
        [[x + 1, y], [x - 1, y], [x, y + 1], [x, y - 1]].forEach(([t1,t2]) => {
            console.log(t1,t2)
            if(matrix[t1] && matrix[t1][t2] && matrix[t1][t2] !== 'W') {
                queue.push({x: t1, y: t2, len: len + 1});
                // Mark as visited
                matrix[t1][t2] = 'W';
            }
        });

    }

    return false;
}


console.log(pathFinder2(
    `.W.
    .W.
    ...`)) // 4