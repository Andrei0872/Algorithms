/*

	Link to this problem : http://www.codewars.com/kata/reverse-or-rotate/train/cpp

	

	Examples:
		@param 1 = the string
		@param 2 = se size of the chunk
		("123456987654", 6) --> "234561876549"
		("123456987653", 6) --> "234561356789"
		("66443875", 4) --> "44668753"
		("66443875", 8) --> "64438756"
		("664438769", 8) --> "67834466"
		("123456779", 8) --> "23456771"
		("", 8) --> ""
		("123456779", 0) --> "" 
		("563000655734469485", 4) --> "0365065073456944"



	Task : {
		for every chunk i must check if the sum of the digits' cubes is even or not
		if the sum is even, i must reverse the string, otherwise i have to rotate it by 1 position 		
	}	
		
	

 	Reasoning :{
 		- i will implement a recursive function (in case there are multiple chunks)
 		- in order to decide whether the sum is even or not, it is enough to know these things {
 			the sum of 2 even numbers will be even
 			the sum of 1 even number and one odd number will be odd
 			the sum of 2 odd numbers will be also even
 		},
 		knowing that we must ensure that, in our chunk, we have have an EVEN number of odd numbers occurrences
 		for example : {
 			if the chunk is : 6644 - the sum is even because we have an even number of odd number occurrences (0 occurrences in this case)
 			if the chunk is : 123456 -  the sum is ODD, because we have 3 odd numbers which will cause the sum to be also odd	
 		}
 		
 		moving farther, 
 			if the sum is even, we will simply apply the reverse function
 			if the sum is odd, we will not use the rotate function, but we will rotate the chunk using the substr(); you will see			
 	} 


*/

// Let's start!

#include <iostream>
#include <string>
#include <algorithm> // reverse() 

using namespace std; // so I don't have to type every time std::


string fun(const string &str, int size) {

	// we first check if it is possible to get any chunks
	if(size < 0 || size > str.length() || str.empty()) {
		return "";
	}	
	
	// we start getting the chunks
	// Remember! We are using recursion
	string chunk = str.substr(0,size);
	
	// we need a variable which will help us know whether the sum is even or not
		bool isEven = true; 
	
	// now we check the sum, applying that reasoning explained above.
	for(int i=0;i<chunk.length();i++) {
		if(chunk[i] % 2 !=0) {
			// we reverse the isEven variable, so if we have an even number of odd numbers, the isEven will always equal to TRUE
			isEven = !isEven; 
		}
	}
	
	// if the sum turns out to be even
	if(isEven) {
		// reverse the string 
		reverse(chunk.begin(),chunk.end());
		
		// then try to find other chunks, by using the + operator, in order to concatenate the next results(if there is any)
		return chunk + fun(str.substr(size),size);
	}
	
	
	// if the sum is odd
	
	// we add the first letter of the chunk to the end
	chunk += chunk[0];
	
	// then we apply the rotation by using substr() and looking for other chunks
	return chunk.substr(1) + fun(str.substr(size),size); 
		
} // end of function


int main () {

	cout << fun("123456987654", 6) << "\n";  //expected 234561876549
	
	cout << fun("66443875",4) << "\n"; // expected 44668753
	
	return 0;
	
}














