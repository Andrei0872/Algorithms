

package DP;

import java.util.Stack;
import java.util.Scanner;

/**
 * Largest rectangle of 1 
 * 
 * Reasoning : {
 * 	1) Use a function that returns the largest rectangular area in a histogram
 *  2) In the matrix, we will use the function I mentioned above on every line
 *  3) If mat[row][col] == 1 : add the item which is above : mat[row][col] += mat[row-1][col]
 * }
 *
 * Example {
 *
 * 	1110
 *	1100
 *	1100
 *	0011
 *
 * Output : 6
 * 
 * }
 * 
 * */


public class LargestRectangle {
	
	static int col,row;
	static int [][] mat;
	static Scanner userInput = new Scanner(System.in);
	
	public static void get_user_input() {
		userInput.hasNextInt();
		row = userInput.nextInt();
		
		userInput.hasNextInt();
		col = userInput.nextInt();
		
		mat = new int[row][col];
		
		for(int i = 0; i < row; i++) {
			for(int j =0; j < col; j++) {
				userInput.hasNextInt();
				mat[i][j] = userInput.nextInt();
			}
		}
		
		for (int i = 0; i < mat.length; i++) {
			for (int j = 0; j < mat[0].length; j++) {
				System.out.print(mat[i][j]);
			}
			System.out.print("\n");
		}
		
	}	
	
	// Get largest rectangular area in histogram
	public static int largestArea(int [] arr) {
		int len = arr.length;
		Stack<Integer> heights = new Stack<Integer>();
		int index = 0;
		int top_value;
		int current_area, max_area = -1;
		while(index < len) {
			
			// Keep adding until the current a[i] is less than the maximum value from stack
			if(heights.empty() || arr[heights.peek()] <= arr[index]) {
				heights.push(index++);
			} else {
				// Adjust the stack
				
				// Get the top value from stack and remove it in order to get the index where the second maximum value is
				// In order to get the right value, multiply the top value with the current index - 1, if the stack is not empty
				// If the stack is empty, simply multiply it by the current index, since there is no other "second maximum value"
				top_value = arr[heights.peek()];
				heights.pop();
				current_area = top_value * (heights.empty() ? index : index - heights.peek() - 1);
				max_area = Math.max(max_area, current_area);
			}
			
		}
		
		// Also have to clear the queue
		// We will apply the same logic
		while(!heights.empty()) {
			
			top_value = arr[heights.peek()];
			heights.pop();
			current_area = top_value * (heights.empty() ? index : index - heights.peek() - 1);
			max_area = Math.max(max_area, current_area);
		
		}
		
		return max_area;
	}
	
	public static int get_area_matrix(int[][] mat) {
		
		// Get the largest area in histogram for the first line
		int current_max_area = largestArea(mat[0]);
		
		for(int i = 1; i < mat.length; i++) {
			for(int j = 0; j < mat[0].length;j++) {
				
				// Check if we can enlarge the area
				if(mat[i][j] == 1) {
					mat[i][j] += mat[i-1][j];
				}
				
			}
			
			// Update the maximum area 
			current_max_area = Math.max(current_max_area, largestArea(mat[i]));
		}
		
		return current_max_area;
	} 
	
	public static void main(String[] args) {
		
		get_user_input();
		System.out.println(get_area_matrix(mat));
	}
	
}


