//* First alternative
function zeros(n) {

    // The number of zeros of a factorial number is biggest value between the number of exponential occurrences of 2 and 5 

    // The number of exponential occurrences of 2
   var exp2 = 0; 

    // The number of exponential occurrences of 5
    var exp5 =0;

    // Determine the occurrences of 2
 
    while(n%2 == 0 ) {
        exp2++;
        n = n / 2;
    }
 

    // Determine the occurrences of 5
    
    while(n%5 == 0 ) {
        exp5++;
        n = n / 5;
    }
    

    // Return the biggest value
    return exp2 > exp5 ? exp2:exp5;

}


//* Second alternative
function zeros2(n) {

    
    var z = 0;

    while(n > 0) {
        n = Math.floor(n/5);
        z += n;
    }

    return z;

}

console.log(zeros(12)); // 12! = 479001600 -> 2 
console.log(zeros(6)); // 6! = 720 ->1

console.info("-------------------");


console.log(zeros2(12)); // 12! = 479001600 -> 2 
console.log(zeros2(6)); // 6! = 720 ->1
