/*

you can find this task  here :  https://www.codewars.com/kata/550554fd08b86f84fe000a58

#Example1

a1 = ["arp", "live", "strong"]

a2 = ["lively", "alive", "harp", "sharp", "armstrong"]

returns ["arp", "live", "strong"]



#Example 2: a1 = ["tarp", "mice", "bull"]

a2 = ["lively", "alive", "harp", "sharp", "armstrong"]

returns []



*/

function inArray(array1,array2){

	// to check if an item from array1 is part of one of the elements of array2  
    let exists =  function (item) {
        
        // initially haven't found the item
        let found = 0;
        
        array2.map(item2 => {
          if(item2.includes(item)) {
            found = 1;
          }
        });
        
      // could be 1 or 0
      return found;
      
    }
   
   // filter array1 
   return array1.filter(item=> {
       
       // keep this item if it is part of one of the elements from array2
       return exists(item);
       
    }).sort(); // we sort the final array
    
}



/* Other examples  */

a2 = ["lively", "alive", "harp", "sharp", "armstrong"]

a1 = ["xyz", "live", "strong"]
Test.assertSimilar(inArray(a1, a2), ["live", "strong"])
a1 = ["live", "strong", "arp"]
Test.assertSimilar(inArray(a1, a2), ["arp", "live", "strong"])
a1 = ["tarp", "mice", "bull"]
Test.assertSimilar(inArray(a1, a2), [])



