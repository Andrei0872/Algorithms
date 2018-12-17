
// https://www.codewars.com/kata/sum-by-factors/javascript

function sumOfDivided(lst) {
    let maxNum = Math.max(...lst),
        marked = [...Array(maxNum +  1)].map(_ => false),
        primes = [];
    
    for(let i = 2; i <= maxNum; i++) {
        if(marked[i]) continue;
    
        let sum = 0, isMultiple = false;
        lst.forEach(item => item % i === 0 ? (sum += item, isMultiple = true): null);
        if(isMultiple) primes.push([i, sum])

        // Mark the non-prime numbers
        for(let j = 2 * i; j <= maxNum; j += i)
            marked[j] = true;
    }
    
    return primes;
}

console.log(sumOfDivided([12,15])) // ​​​​​[ [ 2, 12 ], [ 3, 27 ], [ 5, 15 ] ]​​​​​