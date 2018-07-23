/**
 * Given a number "n", find the prime factor decomposition of n
 * 
 * You can also find it on Codewars : https://www.codewars.com/kata/primes-in-numbers/train/javascript
 *  
 * Reasoning {
 *  1) Loop through prime numbers using a for loop (which will start with the value of 2 - the first prime number)
 *  2) For every prime number, find the number of occurrences
 *  3) If the number of occurrences is not 0, then is fine; else, do not attach to the "output" variable
 *  4) Look for other prime factors until "n" is bigger than 1
 * }
 * 
 */



//* First alternative - using for loops
function primeFactors(n){
    
    var output ='';
    var d,m;
   
    // Loop through prime factors..
    for(d = 2; n > 1; d++) { 
        
        // Determine the number of occurrences for a prime factor
        // m = 0 - number of occurrences
        // n%d == 0 - the condition to be fulfilled
        // n = Math.floor(n/d) - search for other factors
        for(m = 0; n%d == 0; m++, n = Math.floor(n/d));

        // If the prime factor exists (number of its occurrences is not 0)
        if(m != 0) {
            output += m !=1 ? '(' +  d + '**' + m + ')' : '(' + d + ')';
        }

    }


    return output;

}


//* Second alternative - using while loops
// The reasoning is the same as the first alternative
function primeFactors2(n) {

    var output ='';

    // Prime factors
    var d =2;
    
    // The number of occurrences for a prime factor
    var p;

    while(n > 1) {

        // Initially, the number of occurences is 0
        p = 0;
        
        // Determine the number of occurrences for a prime number
        while(n%d == 0) {
            p++;
            n = Math.floor(n/d);
        }

        // If the number of occurrences is not 0!
        if(p) {
            output += p!=1 ? '(' +  d + '**' + p + ')' : '(' + d + ')';
        }

        // Search of other prime numbers
        d++;
    }
    return output;

}

// First alternative 
console.log(primeFactors(7775460)); // (2**2)(3**3)(5)(7)(11**2)(17)
console.log(primeFactors(45)); // (3**2)(5)
console.log(primeFactors(120)); // (2**3)(3)(5)

console.log("-------------------");

// Second alternative
console.log(primeFactors2(7775460)); // (2**2)(3**3)(5)(7)(11**2)(17)
console.log(primeFactors2(45)); // (3**2)(5)
console.log(primeFactors2(120)); // (2**3)(3)(5)
