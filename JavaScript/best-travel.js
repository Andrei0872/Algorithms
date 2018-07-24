
// Link to the task : https://www.codewars.com/kata/best-travel/train/javascript

/**
 * Reasoning {
 * 1) Set a recursive function that will get arrays with k elements each
 * 2) For every array of that kind, calculate the sum of it, and than compare with the biggest limit found until that moment
 * 3) The validation we'll be done automatically, thanks to this statement :  if(choiceArr.length == k)
 * }
 */


function chooseBestSum (t,k,ls) {

    // The value that we'll return
    var maxLimit = 0; 

    // A recursive function that will get the choices array    
    function getChoices(choiceArr, lastIndex) {

        // Initially the array is empty, but, as we go further, it might already have some values
        choiceArr = choiceArr || [];

        // Check if the choice array has "k" elements
        if(choiceArr.length == k) {
            
            // Get the sum of the array
            var sumOfArr = choiceArr.reduce((acc,item)=>acc+item);

            // Check if we can find the biggest value
            if(sumOfArr <= t && sumOfArr > maxLimit) {
                maxLimit = sumOfArr;
            }

            // Stop here, and check for other solutions
            return;

        }

        // Loop through the list elements
        // Here we'll also use recursion

        // Initially lastIndex won't be defined
        // After lastIndex is defined we want to get only the elements after the lastIndex : lastIndex + 1
        for(var i = lastIndex + 1 || 0; i < ls.length; i++) {
            
            // Call this function for every element
            // use concat() in order to create the choices arrays
            getChoices(choiceArr.concat(ls[i]),i); // From here it will take elements after current lastIndex and so on..

        }

    }

    // Call the recursive function
    getChoices();

    // Return the biggest limit found
    return maxLimit != 0 ? maxLimit : null;


}





console.log(chooseBestSum(163,3,[50, 55, 56, 57, 58])); // 163
console.log(chooseBestSum(163,3,[50])); // null
console.log(chooseBestSum(230,3,[91, 74, 73, 85, 73, 81, 87])); // 228
console.log(chooseBestSum(174,3,[50, 55, 57, 58, 60])); // 173

