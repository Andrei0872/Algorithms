

//* Range Extraction

// https://www.codewars.com/kata/range-extraction/train/javascript

function solution (list) {

    // Store ranges
    const ranges = [[list[0]]]

    // Current range start
    let currentRange = ranges[0];

    // Start with the second element
    for(let i = 1; i < list.length; i++) {

        const currentNumber = list[i];
        const lastValueInRange = currentRange[currentRange.length - 1];

        // If the current number is in the range
        if(Math.abs(currentNumber - lastValueInRange) === 1) {
            
            // Push into current range array
            currentRange.push(currentNumber);
        
        }else {
        
            currentRange = [currentNumber];
            ranges.push(currentRange)
        }

    }
    // console.log(ranges)

    // Get the array that contains only the limits
    const result = ranges.map(range => {
        console.log(range)
        if(range.length === 1) return '' + range;
        if(range.length === 2) return range.join(",");
        return '' + range[0] + '-' + range[range.length-1]
    })
    // console.log(result)
    return result.join(',')
}

console.log(solution([-6, -3, -2, -1, 0, 1, 3, 4, 5, 7, 8, 9, 10, 11, 14, 15, 17, 18, 19, 20]), "-6,-3-1,3-5,7-11,14,15,17-20")


