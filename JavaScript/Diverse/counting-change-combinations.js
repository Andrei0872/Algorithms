
// Task(show only the number of combinations) :  https://www.codewars.com/kata/counting-change-combinations/train/python

/**
 * Write a function that counts how many ways you can change for that for an amount of money, 
 * given an array of coin denominations.
 * 
 * Example {
 *  1) sum = 4, coins = [1,2]
 *  Output : 1 1 1 1;  1 1 2; 2 2;
 * }
 * 
 * 
 * In this case, we are going to count the number of combinations and print each combination
 * We will use Backtracking in order to achieve that
 * 
 * Reasoning : {
 *  1) Keep adding elements until one of the base cases is encountered
 *  2) If "money === 0", it means we have a combination; print it.
 *  3) Each time we go back, we delete that last element in order to get all the combinations
 * }
 * 
 */

let result = []
let cnt = 0;
function getResult(money,coins) {

    // Base cases
    if(money < 0 || coins.length === 0 ) {
        return; // Stop
    }
    if(money ===  0) {
        // Count number of options
        cnt++;
        console.log("Option " + cnt );
        for(elem of result){
            console.log(elem)
        }
        return; // Stop
    }
    
    // Start by adding the first element in the coins array
    result.push(coins[0]);
    getResult(money - coins[0], coins);
    result.pop(); // Backtracking
    getResult(money, coins.slice(1));
}
 
getResult(4,[1,2]); 
console.log(cnt) // 3

cnt = 0;
getResult(10, [5,2,3])
console.log(cnt) // 4

cnt = 0
getResult(11, [5,7])
console.log(cnt) // 0

