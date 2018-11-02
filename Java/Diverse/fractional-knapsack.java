


package greedy;
import java.util.*;
import java.io.*;

/**
 * Fractional Knapsack Problem
 * 
 * Given weights and values of n items and a capacity W
 * determine the maximum total value in the knapsack
 * 
 * Example : {
 * Input : (value,weight)
 * arr = {{60, 10}, {100, 20}, {120, 30}}
 * W = 50
 * Output : 240 (full items of 10, 20 and 2/3 of the last item of 30)
 * }
 * 
 * */

class Item {
	int value,weight;
	public Item(int value, int weight) {
		this.value = value;
		this.weight = weight;
	}
}

class SortByRatio implements Comparator<Item> {
	
	public int compare(Item a, Item b) {
		int r1 = (int) a.value / a.weight;
		int r2 = (int) b.value / b.weight;
		return r1 - r2;
	}
	
}
 
public class FractionalKnapsack {
	static ArrayList<Item> arr = new ArrayList<Item>();
	static Scanner userInput = new Scanner(System.in);
	static int n,W;
	
	public static void getInput() {
		userInput.hasNextInt();
		n = userInput.nextInt();
		
		userInput.hasNextInt();
		W = userInput.nextInt();
		
		int val, w;
		
		for(int i =0; i < n;i++) {
			userInput.hasNextInt();
			val = userInput.nextInt();
			
			userInput.hasNextInt();
			w = userInput.nextInt();
			arr.add(new Item(val,w));
		}
	}
	
	public static double solve() {
		// Sort the array in desc order accordion to value/weight
		Collections.sort(arr, new SortByRatio() );
		
		int currentWeight = 0;
		double finalVal =  0.0;
		
		for(int i =0; i < arr.size(); i++) {
			// If adding a new weight won't overflow
			if(currentWeight + arr.get(i).weight <= W) {
				currentWeight += arr.get(i).weight;
				finalVal += arr.get(i).value;
			}else {
				// Get the ramaining part
				int remain = W - currentWeight;
				finalVal += arr.get(i).value * ((double) (remain / arr.get(i).weight) );
				break;
			}
		}
		
		return finalVal;
		
	}
	
	public static void main(String[] args) {
		
		getInput();
		System.out.println(solve());
	}
	
}


