# https://www.codewars.com/kata/k-primes/train/python

def find_primes (n):
    total, i = 0, 2

    while i * i <=n:
        while n % i == 0:
            total += 1
            n //= i
        i += 1

    if n > 1: total += 1 

    return total

def count_Kprimes(k, start, nd):
    return [x for x in range(start, nd + 1) if find_primes(x) == k]

def puzzle(s):
    onePrimes = count_Kprimes(1, 2, s)
    threePrimes = count_Kprimes(3, 2, s)
    sevenPrimes = count_Kprimes(7, 2, s)

    return sum([onePrime + threePrime + sevenPrime == s for onePrime in onePrimes for threePrime in threePrimes for sevenPrime in sevenPrimes])


print(count_Kprimes(5, 500, 600))

