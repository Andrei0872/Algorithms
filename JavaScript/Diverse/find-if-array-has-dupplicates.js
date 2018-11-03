
// Find if an array contains duplicates 

function valid (arr) {
    
    // We didn't find any duplicate yet
    var dup = false;

     arr.reduce((acc,item) =>{

        // If the accumulator is not empty and the item is present in the array
        if(acc.length !=0 && acc.indexOf(item) != -1)
            dup = true; // It means we have a dupplicate

        
        acc.push(item);
        return acc;    

    },[]); // Accumulator starts as an empty array : []

return dup;

}



console.log(valid([1,2,3,1])); // true
console.log(valid([1,2,3,4,5,6])); // false
console.log(valid([1,2,3,6,3,2,1])); // true
