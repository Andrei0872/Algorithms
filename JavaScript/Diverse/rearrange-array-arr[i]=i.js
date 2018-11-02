
// Rearrange array such that arr[i] = i

// We'll use an array to store the position of the given array

function rearrange(arr){

    const len = arr.length;
    let posArr = []
     
    // Store the positions
    for(pos of arr) {
        console.log(pos)
        posArr.push(pos);
    }

    // Loop through the original array and see if the value at a certaing index is defined
    for(let i =0 ; i < len; i++) {

        if(typeof posArr.find((elem) => elem == i) !== 'undefined')
            arr[i] = i
        else 
            arr[i] = -1
    }

    // Print the array
    for(elem of arr) {
        console.log(elem)
    }

}

const arr = [1, -1, 6, 1, 9,
    3, 2, -1, 4,-1]
// rearrange(arr) // -1, 1, 2, 3, 4, -1, 6, -1, -1, 9

const arr2 =[19, 7, 0, 3, 18, 15, 12, 6, 1, 8,
    11, 10, 9, 5, 13, 16, 2, 14, 17, 4]  
rearrange(arr2) // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19


