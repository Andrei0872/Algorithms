

// Matrix Determinant

// https://www.codewars.com/kata/52a382ee44408cea2500074c/train/javascript


function determinant(m) {

    // Base cases
    if(m.length == 1)
        return m[0][0]

    if(m.length == 2) {
        return (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]) 
    }

    let det;
    for(let col = 0; col < m.length; col++) {

        // Get the filtered matrix
        let filteredMatrix = m.map((row,rowIndex) => // Get every row
                            row.filter((item,itemIndex)=> // Filter every element within a row
                            rowIndex !=0 && itemIndex != col)) // Get the right maxtrix
                            .filter(row => row.length !=0); // Get rid of empty rows
        

        if(col == 0) {
            det =  m[0][0] * determinant(filteredMatrix);
            continue;
        }
        
        // console.log(filteredMatrix)
        let multiplier = col % 2 == 1 ? -m[0][col] : m[0][col]
        let res = multiplier * determinant(filteredMatrix);
        det += res; 
    }
    return det;
}

// const m1 = [[1,3],[2,5]]
// const m2 = [ [2,5,3], [1,-2,-1], [1, 3, 4]]
// const m3 = [[2,5,3,6], [1,-2,-1,2], [1, 3, 4,1],[1,2,3,4]];

// console.log(determinant([[1]]), 1)
// console.log(determinant(m1),-1)
// console.log(determinant(m2),-20)
// console.log(determinant(m3),-20)

// const m4 = [[2,4,2],[3,1,1],[1,2,0]];
// console.log(determinant(m4),10)

// const m5 = [[ 2, 4, -3 ], [ 1, 8, 7 ], [ 2, 3, 5 ] ];
// console.log(determinant(m5),113)

// const m5 = [ [ 1, 2, 3, 4 ], [ 5, 0, 2, 8 ], [ 3, 5, 6, 7 ], [ 2, 5, 3, 1 ] ]
// console.log(determinant(m5),24)



