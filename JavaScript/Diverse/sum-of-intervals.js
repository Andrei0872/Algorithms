
//* Sum of intervals

// https://www.codewars.com/kata/sum-of-intervals

function sumIntervals(intervals){
    
    let result = []

    for(let i = 0; i < intervals.length; i++) {
        for(let j =intervals[i][0]; j<intervals[i][1];j++) {
            result.push(j);
        }
    }   

    // Avoid overlaps
    return [...new Set(result)].length

  }

var test1 = [[1,5]];
console.log(sumIntervals(test1)) // 4

var test2 = [[1,5],[6,10]];
console.log(sumIntervals(test2)) // 8

var test3 = [[1,5],[1,5]];
console.log(sumIntervals(test3)) // 4

var test4 = [[1,4],[7, 10],[3, 5]];
console.log(sumIntervals(test4)) // 7

