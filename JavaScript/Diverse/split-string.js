/*

link to the task : https://www.codewars.com/kata/split-strings/train/javascript

This is a very basic way of solving this task.

It could've been solved with just one line : 
	return (str.length % 2 ==0 ? str : str + "_").match(/../g);

*/

function solution(str){

  const pair = 2;
  let output = []; 
  let i,j;

   // Determine how many pairs 
    let nrp = Math.floor(str.length / pair);



  // Check first the length of the string
  
  if(str.length % 2 == 0) {
    // Even number of chars
    
      // We keep applying the substr() function, depending on the number of pairs we can have
      // j variable helps us getting the output
      for( i = 1, j = 0; i <= nrp; i++, j+=2) {
        
        output.push(str.substr(j,pair));
      
      }
    
  
  } else {
    // Odd number of chars
      
//       if(str.length >= nrp) {}
      for( i = 1, j = 0;i <= nrp ; i++, j+=2) {
        output.push(str.substr(j,pair));
      }
      
      // Having an odd number of chars, we must get the last char and add the _ to id
      output.push(str[str.length-1] + "_");
    
  }  

  return output;

   
}


// TODO: Replace examples and use TDD development by writing your own tests


// These are some CW specific test methods available:
//    Test.expect(boolean, [optional] message)
//    Test.assertEquals(actual, expected, [optional] message)
//    Test.assertSimilar(actual, expected, [optional] message)
//    Test.assertNotEquals(actual, expected, [optional] message)

// NodeJS assert is also automatically required for you.
//    assert(true)
//    assert.strictEqual({a: 1}, {a: 1})
//    assert.deepEqual({a: [{b: 1}]}, {a: [{b: 1}]})

// You can also use Chai (http://chaijs.com/) by requiring it yourself
// var expect = require("chai").expect;
// var assert = require("chai").assert;
// require("chai").should();

describe("Solution", function(){
  it("should test for something", function(){
    Test.assertEquals("actual", "expected", "This is just an example of how you can write your own TDD tests");
  });
});


