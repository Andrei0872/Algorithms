
// https://www.codewars.com/kata/snail/train/javascript

const snail = function (array) {
    let rows = array.length;
    let cols = array[0].length;
    let r = 0, c = 0;
    const result = [];
    
    while(r < rows && c < cols) {
      for(let i = c; i < cols; i++)
        result.push(array[r][i]);
      // Go to the next row
      r++;

      for(let i = r; i < rows; i++)
        result.push(array[i][cols-1]);
      // Go to the prev column
      cols--;
      
      // Are there any rows to print ?
      if(r < rows) {
        for(let i = cols - 1; i >= c; i--)
          result.push(array[rows - 1][i]);
        rows--;
      }
      // Are there any columns to print ?
      if(c < cols) {
        for(let i = rows - 1; i >= r; i--)
          result.push(array[i][c])
        c++;
      }
    }
    return result;
}

let array = [[1,2,3],
             [4,5,6],
             [7,8,9]]

console.log(snail(array)) // ​​​​​[ 1, 2, 3, 6, 9, 8, 7, 4, 5 ]​​​​​