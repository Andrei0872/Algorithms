// https://www.codewars.com/kata/es5-generators-i/train/javascript

function generator(sequencer) {
    // return {
    //     next : sequencer.apply(null,[].slice.call(arguments,1))
    // };
    return {
        next : arguments[0].apply(null,[].slice.call(arguments,1))
    };
}

function dummySeq() {
    return function () {
        return "dummy";
    };
}

function factorialSeq() {
    let [pos, count] = [0,1];
    return function () {
        if(pos === 0 ) { pos++; return count; }
        return count *= pos++;
    }
}

function fibonacciSeq() {
    let current = 1, next = 1, last;
    return function () {
        last = current;
        current = next;
        next = current + last;
        return last;
    }
}

function rangeSeq(start, step) {
    return function () {
        let tmp = start;
        start += step;
        return tmp;
    }
}

function primeSeq() {
    var count = 0;
    return function() {
      if(sieve[count] == null) generateNextPrime();
      return sieve[count++];
    }
  }

function partialSumSeq() {
    let sequence =  [].slice.call(arguments);
    let pos = 0, current = sequence[pos];
    return function () {
        let temp = current;
        current += sequence[++pos];
        return temp;
    }
}

var sieve = [2,3,5,7,11];
function generateNextPrime() {
  var current = sieve[sieve.length - 1] + 2;
  while (true) {
    if (isPrimeFromSieve(current)) {
      sieve.push(current);
      break;
    }
    current += 2;
  }
}

function isPrimeFromSieve(num) {
    var max = Math.ceil(Math.sqrt(num));
    for (var i = 0; i < sieve.length; i++) {
      if (num % sieve[i] === 0) return false;
      else if (max < sieve[i]) return true;
    }
    return true;
}

    var seq = generator(dummySeq);
    console.log(seq.next(), 'dummy');
    console.log(seq.next(), 'dummy');
    console.log(seq.next(), 'dummy');

    // ====================================================

    var seq = generator(factorialSeq);
    console.log(seq.next(), 1); // 0! = 1
    console.log(seq.next(), 1); // 1! = 1
    console.log(seq.next(), 2); // 2! = 2
    console.log(seq.next(), 6); // 3! = 6
    console.log(seq.next(), 24); // 4! = 24
    
    // ====================================================

    var seq = generator(fibonacciSeq);
    console.log(seq.next(), 1); // fib(0) = 1
    console.log(seq.next(), 1); // fib(1) = 1
    console.log(seq.next(), 2); // fib(2) = 2
    console.log(seq.next(), 3); // fib(3) = 3
    console.log(seq.next(), 5); // fib(4) = 5
    console.log(seq.next(), 8); // fib(5) = 8
    console.log(seq.next(), 13); // fib(6) = 13

    // ====================================================

    var seq = generator(rangeSeq, 5, 3); // 5,8,11,14,17
    console.log(seq.next(), 5);
    console.log(seq.next(), 8);
    console.log(seq.next(), 11);
    console.log(seq.next(), 14);

    // ====================================================

    var seq = generator(primeSeq);
    console.log(seq.next(), 2);
    console.log(seq.next(), 3);
    console.log(seq.next(), 5);
    console.log(seq.next(), 7);
    console.log(seq.next(), 11);
    console.log(seq.next(), 13);
    console.log(seq.next(), 17);
    console.log(seq.next(), 19);

    // ====================================================

    var seq = generator(partialSumSeq, -1, 4, 2, 5);
    console.log(seq.next(), -1);
    console.log(seq.next(), 3);
    console.log(seq.next(), 5);
    console.log(seq.next(), 10); //End of sequence
    
    // Test.expectError('End of sequence error expected', seq.next);


