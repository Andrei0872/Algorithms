
package DP;

import java.util.Scanner;


//Given two strings, determine how many changes are needed to apply on the first string
//in order to be identical to the second one

/*
Changes available :
- remove a letter
- insert a letter
- replace a letter

Example : {

s1 = "ana"
s2 = "alla"
Output : 2

The Matrix : 

0	1	2	3	4	
1	0	1	2	3	
2	1	1	2	3	
3	2	2	2	2

} 

Reasoning : {
 1) We need to determine the minimum number of changess needed to
    "match" first "i" characters from the first string with
    first "j" characters from the second string
 2) We'll use a matrix C[][]
 3) C[i][j] = k -  - in order to match the first "i" ch. from s1 with the first "j" ch from s2 we need "k" changes
 4) We will to use the strings as 1 indexed strings because it will easier to use the matrix
}
*/


public class How_Many_Missing_Letters {
	
	static Scanner userInput = new Scanner(System.in);
	// Manipulate strings easier
	static StringBuffer s1,s2; 
	static int[][] C = new int [100][100];
 	
	
	public static void getInput() {
		
		userInput.hasNext();
		s1 = new StringBuffer(userInput.next());
				
		userInput.hasNext();
		s2 = new StringBuffer(userInput.next());

		// Make the strings 1 indexed
		s1.insert(0, "1");
		s2.insert(0, "1");
		
	}

	public static int min(int a, int b, int c) {
		return a < b ? a < c ? a:c : b < c ? b : c;
	}
	
	public static int countChanges() {
		
	    // That makes a lot of sense..
	    // C[0][0] = 0; // No changes are required to match the first 0 ch of the first and second string
	    
		int len1 = s1.length()-1;
		int len2 = s2.length()-1;
		
	    // We'll need "i" changes to match the first "i" ch from the first string with the first 0 ch from second string
	    for(int i =1; i <= len1;i++)
	        C[i][0] = i;

	    // We'll need "j" changes to match first 0 ch from the first string with the first "j" ch from second string
	    for(int j=1; j <= len2;j++)
	        C[0][j] = j;
		
	    for(int i=1;i <= len1; i++) {
	    	for(int j =1; j <= len2; j++) {
	    		// If we found a match, there is no change to be made
	    		if(s1.charAt(i) == s2.charAt(j)) {
	    			C[i][j] = C[i-1][j-1];
	    		}else {
	    			// + 1 - Because a change has been made
	    			C[i][j] = min(C[i][j-1],C[i-1][j],C[i-1][j-1]) + 1;
	    		}
	    	}
	    }
	    
	    // Print the matrix to get a better idea
	    for (int i = 0; i <= len1; i++) {
			for (int j = 0; j <=len2; j++) {
				System.out.print(C[i][j] + "\t" );
			}
			System.out.print("\n");
		}
	 
	    return C[len1][len2];
	    
	}
	
	public static void main(String[] args) {
		getInput();
		System.out.println(countChanges());
	}
	
}
