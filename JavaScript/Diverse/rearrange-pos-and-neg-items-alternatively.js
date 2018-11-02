

// Rearrange positive and negative numbers alternatively

/**
 * Example : {
 *  arr =  [-1, 2, -3, 4, 5, 6, -7, 8, 9]
 *  Output : [9, -7, 8, -3, 5, -1, 2, 4, 6]
 *  
 * }
 * 
 * Reasoning {
 *  1) We will use the partition process of QuickSort to determine 
 *    the position from where the arrays contains only positive numbers
 *  2) Having that position, every element with  i < pos will be negative
 *  3) Start swapping, by starting from the first negative element(position = 0 ) 
 * }
 * 
 * 
 */

function rearrange(arr) {

    const len = arr.length

    // QuickSort partition process
    var j = -1;
    for(var i = 0; i <  len; i++ ) {
        if(arr[i] < 0) {
            j++;
            // Swap the elements
            arr[j] = [arr[i],arr[i]=arr[j]][0]
        }
    }
    // j -  the last position of a negative element
    
    // From here the array contains only positive numbers
    let pos = j + 1
    // The start position of negative elements
    let neg = 0;
    // let [neg,pos] = [0,j+1]

    // Swap the elements
    while(neg < pos && pos < len &&  arr[neg] < 0) {

        arr[neg] = [arr[pos],arr[pos] = arr[neg]][0]
        pos++; // Go to the next positive item
        neg += 2; // Go to the next negative item

    }

    return arr;

}

const arr =[-1, 2, -3, 4, 5, 6, -7, 8, 9]
console.log(rearrange(arr)) // [4-3,5,1,6,-7,2,8,9]


