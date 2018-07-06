

function nextSmaller(n) {

var promise = new Promise(function(resolve,reject) {
    
      var biggerIndex; 
      var i,j;
      var exists = false; 
    
    //we first get the string as an array, bcs we ll need to loop through it
      var str = n.toString().split('');
     //we find the LAST element which is bigger than the element next to it
      // i <str.length-1 bcs we will check  [i+1]..
      for( i = 0; i <str.length-1;i++) {
       if(str[i] > str[i+1]) {
           biggerIndex = i; //we save the index
              exists = true; //we keep looking, bcs we need the bigger number which is smaller then "n"
          }
      }
      
      if(!exists || str[0] == 0) {
       reject('-1');
 
      }else {
       
         //we now look for the first element which is less than the element found at the biggerIndex
      //we start from the end of the array
      for(j = str.length-1;j>0;j++) {
       if(str[j] < str[biggerIndex]) {
        
           //if this is true, then we swap them
              var temp;
              temp = str[j];
              str[j] = str[biggerIndex];
              str[biggerIndex] = temp;
    break; //no need to look further
          }
      }
      
      
        var response =  parseInt(str.slice(0,biggerIndex+1).concat(str.slice(biggerIndex+1).sort(function(a,b) {return parseInt(b) - parseInt(a);})).join(''));       
      resolve(response);
      }
    
});
var x;
promise.then(function(resp) {

    document.write(resp);
    
}).catch(function(err) {
 document.write(err);
});


return x;
}


Test.describe("Fixed tests", function() {
	Test.it("Smaller numbers", function() {
    Test.assertEquals(nextSmaller(21), 12)
 		Test.assertEquals(nextSmaller(907), 790)
		Test.assertEquals(nextSmaller(531), 513)
		Test.assertEquals(nextSmaller(135), -1)
		Test.assertEquals(nextSmaller(2071), 2017)
		Test.assertEquals(nextSmaller(1027), -1)
		Test.assertEquals(nextSmaller(414), 144)
	})
  
	Test.it("Bigger numbers", function() {
		Test.assertEquals(nextSmaller(123456798), 123456789)
		Test.assertEquals(nextSmaller(123456789), -1)
		Test.assertEquals(nextSmaller(1234567908), 1234567890)
	})
})


