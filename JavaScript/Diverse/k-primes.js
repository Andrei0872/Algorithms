// https://www.codewars.com/kata/k-primes/train/javascript


function primeFactors(n) {
    let totalFactors = 0;

    for (let factor = 2; n !== 1; factor++) {
        let numFactors = 0
        for (; n % factor === 0; n = Math.floor(n / factor), numFactors++);
        totalFactors += numFactors;
    }

    return totalFactors;
}

function countKprimes(k, start, nd) {
    const result = [];

    for (let i = start; i <= nd; i++) {
        if (primeFactors(i) === k)
            result.push(i);
    }

    return result;
}


function puzzle(s, numPrimes = 0) {
    const onePrimes = countKprimes(1, 2, s);
    const threePrimes = countKprimes(3, 2, s);
    const sevenPrimes = countKprimes(7, 2, s);
    let total = 0;

    for (one of onePrimes)
        for (three of threePrimes)
            for (seven of sevenPrimes)
                total += (one + three + seven === s);

    return total;
}

console.log(puzzle(138)) // 1
console.log(puzzle(143)) // 2
