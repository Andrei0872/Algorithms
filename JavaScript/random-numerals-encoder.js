
/*

Link to the task : https://www.codewars.com/kata/51b62bf6a9c58071c600001b

*/

function solution(number){
  
    // Thousands
    var  m = ["", "M", "MM", "MMM"];
    
    // Hundereds
    var  c = ["", "C", "CC", "CCC", "CD", "D", 
                        "DC", "DCC", "DCCC", "CM"];
    
    // Tens
    var x = ["", "X", "XX", "XXX", "XL", "L", 
                        "LX", "LXX", "LXXX", "XC"];
    
    // Ones
    var  i = ["", "I", "II", "III", "IV", "V", 
                        "VI", "VII", "VIII", "IX"];
         
     // Converting to roman
     // Their name say it all
     var thousands = m[Math.floor(number/1000)];
     var hundereds = c[Math.floor((number%1000)/100)];
     var tens =  x[Math.floor((number%100)/10)];
     var ones = i[number%10];
         
     // We get the final result    
     var ans = thousands + hundereds + tens + ones;
         
     return ans;
  
  
}



// Some other examples

describe("solution", () => {
  it ("should handle small numbers", () => {
    Test.assertEquals(solution(1), 'I', '1 should, "I"')
    Test.assertEquals(solution(2), 'II', '2 should, "II"')
    Test.assertEquals(solution(3), 'III', '3 should, "III"')
    Test.assertEquals(solution(4), 'IV', '4 should, "IV"')
    Test.assertEquals(solution(5), 'V', '5 should, "V"')
    Test.assertEquals(solution(9), 'IX', '9 should, "IX"')
    Test.assertEquals(solution(10), 'X', '10 should, "X"')
    Test.assertEquals(solution(11), 'XI')
    Test.assertEquals(solution(19), 'XIX')
    Test.assertEquals(solution(22), 'XXII')
    Test.assertEquals(solution(15), 'XV')
  });
  
  it ("should handle large numbers", () => {
    Test.assertEquals(solution(1000), 'M', '1000 should, "M"')
    Test.assertEquals(solution(1001), 'MI', '1001 should, "MI"')
    Test.assertEquals(solution(1990), 'MCMXC', '1990 should, "MCMXC"')
    Test.assertEquals(solution(2007), 'MMVII', '2007 should, "MMVII"')
    Test.assertEquals(solution(2008), 'MMVIII', '2008 should, "MMVIII"')
  });
});

