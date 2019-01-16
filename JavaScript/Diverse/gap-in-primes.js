// https://www.codewars.com/kata/gap-in-primes/train/javascript

// First solution

function sieve(n) {
    const res = []
    const primes = [...Array(n + 1)].fill(true)

    for (let i = 2; i * i <= n; i++) {
        if (primes[i]) {
            // Prime number found

            for (let j = i * i; j <= n; j += i)
                primes[j] = false;
        }
    }

    for (let i = 2; i <= n; i++) {
        if (primes[i])
            res.push(i)
    }

    return res
}

function gap(g, m, n) {
    const pair = [];
    let primes = sieve(n);
    let firstPrimeGreater = primes.findIndex(prime => prime >= m)
    primes = primes.slice(firstPrimeGreater, primes.length)

    for (let i = 0; i < primes.length - 1; i++) {
        if (primes[i + 1] - primes[i] === g) {
            pair.push(primes[i], primes[i + 1])
            break;
        }
    }

    return pair.length ? pair : null
}


// Second Solution

function gap(g, m, n) {
    let lastPrime = 0
    const isPrime = x => {
        for (let i = 2; i <= Math.sqrt(x); i++)
            if (x % i === 0)
                return false

        return true
    }

    for (let i = m; i <= n; i++) {
        if (isPrime(i)) {
            if (i - lastPrime === g)
                return [lastPrime, i]
            else
                lastPrime = i
        }
    }

    return null
}

console.log(gap(2, 100, 110), [101, 103]);
console.log(gap(4, 100, 110), [103, 107]);
console.log(gap(6, 100, 110), null);
console.log(gap(8, 300, 400), [359, 367]);
console.log(gap(10, 300, 400), [337, 347]);