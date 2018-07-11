	
	// Link to the task : https://www.codewars.com/kata/52685f7382004e774f0001f7/solutions/javascript

	function humanReadable(seconds) {
  
  
  // A function that will add a zero to the number if needed
  	var addZero = function (num) {return num.toString().length == 1 ?  "0" + num : num;} 		
	
	return addZero(Math.floor(seconds/3600)) + ":" +  // Hours
	
			// seconds % 3600 -  what's left from hours
			 addZero(Math.floor(seconds % 3600 / 60)) + ":" +  /* Minutes */
		   
		   // seconds % 60 - what's left from minutes
			 addZero(seconds % 60); // Seconds
		
	}
	
		
		
	// Other examples 	
	
   	console.log(humanReadable(0)); 
      console.log(humanReadable(5)); 
      console.log(humanReadable(60)); 
	   console.log(humanReadable(86399)); 
      console.log(humanReadable(359999)); 
 

