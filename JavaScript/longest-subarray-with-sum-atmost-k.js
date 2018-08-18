

// Logenst subarray having sub at atmost k 

/**
 * Example : {
 *  1) 
 * arr = [1, 2, 1, 0, 1, 1, 0]
 * k = 4
 * Output : 5 ({1, 0, 1, 1, 0}) 
 * }
 */

function getLength(arr,k) {

    let end = 0,
        begin = 0,
        startPos,
        endPos,
        sum = 0,
        maxLength = -1 

    while(end < arr.length) {

        // Keep adding elements until the sum does not match the condition
        if(sum <= k ) {
            sum += arr[end++]
        } else {
            // Start getting rid of elements that are at the beginning
            sum -= arr[begin++]
        }

        // Get the final results
        if( sum  <= k ) {
            if(maxLength < (end - begin)) {
                maxLength = end - begin
                startPos = begin
                endPos = end - 1
            }
        }

    }
    
    return {maxLength, startPos,endPos}

}

console.log(getLength([1, 2, 1, 0, 1, 1, 0], 4)) // {maxLength : 5, startPos : 2,endPos : 6}

