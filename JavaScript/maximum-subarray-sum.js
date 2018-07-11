
// Link to the task : https://www.codewars.com/kata/54521e9ec8e60bc4de000d6c/solutions/javascript


var maxSequence = function(arr){
 
 	var maxSub = -32000; // Initial max value
 
 	// Let the sum start at 0
 	var sum = 0;
 	
 	// The position where the substring starts
 	var startPos = 0 ; // At first, it's 0	
 	
 	// The position where the substring ends
 	var lastPos;
 	
 	// Here we will save the position where the substring starts after we find the maximum sum
 	var savedFirstPos;
 	
 	// Loop through each element, and add it to the sum		
 	for(var i = 0; i < arr.length ; i++) {
 	
 		
 		// If the sum turns out to be negative, we reset it to 0
 		if(sum < 0) {
 			sum = 0;
 			startPos = i;
 			//We also 
 		}

		sum += arr[i];
 		
 		// Find the maximum sum
 		if(sum > maxSub) {
 			// Update the maximum value
 			maxSub = sum;
 			// Save the initial position
 			savedFirstPos = startPos;
 			// Set the last position
 			lastPos = i;
 			
 		} 
 		
 	}	
 	
 	// Just in case you want to print the substring elements..
 	//for(var i =startPos; i <= lastPos ;i ++) 
 		//console.log(arr[i]);
 	
 	// If the array has only negative numbers, we return 0
 	return maxSub > 0  ? maxSub : 0;
 		
 		
}
 

console.log(maxSequence([-2, 1, -3, 4, -1, 2, 1, -5, 4])); // 6 = 4 + (-1) + 2 + 1

