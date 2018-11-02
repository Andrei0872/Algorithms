
//* Greedy - Intervals to be removed

/**
 *  Given an array of "n" intervals, determine the number of intervals that can be removed
 *
 * An interval can be removed if it is can by contained by another interval
 * 
 * Example {
 * 1) n = 5
 *  intervals : [0,10],[2,9],[3,8],[1,15],[6,11]
 *  Output : 3
 * }
 * 
 */

function intervals_to_remove(intervals) {

    return intervals
        // Sort them by the left "limit"
        .sort((interval1,interval2)=>{
            return interval1[0] - interval2[0]
        })
        .slice(1) // Start from the second element
        .reduce((acc,currentInt)=> {

            // Check if it includes the left limit
            if(acc.top > currentInt[0]) {
                // Check if it includes the right limit
                if(acc.top > currentInt[1]){
                    // It means we can remove an interval
                    acc.removed++
                    // The interval removed
                    console.log(currentInt)
                }else {
                    // Update the top value -  gets the greater value - the right limit in this case
                    acc.top = currentInt[1]
                }
            }else {
                // Update the top value -  gets the greater value - the left limit in this case
                acc.top = currentInt[0]
            }
            return acc;
        },{top:intervals[0][1],removed:0})
        .removed; 

}


let intervals = [[0,10],[2,9],[3,8],[1,15],[6,11]]
console.log(intervals_to_remove(intervals)) // 3

let intervals2 = [[2,3],[5,1],[0,10]];
console.log(intervals_to_remove(intervals2)) // 2

let intervals3 = [[1,9],[5,10],[3,4],[0,5],[2,8]]
console.log(intervals_to_remove(intervals3)) // 2

