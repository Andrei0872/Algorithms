
public class Knapsack {
    
    public static int solve(int W, int weight[], int values[]) {
        int len = weight.length;
        int store[][] = new int[len + 1][ W + 1];

        // i - Looping through the items
        // j - The capacity
        for(int i = 0; i <= len; i++) {
            for(int j = 0; j <= W; j++) {
                // Base cases : capacity = 0 || no more elements
                if(i == 0 || j == 0 ) {
                    store[i][j] = 0;
                } 
                // Is the last elem greater than W ? 
                else if(weight[i - 1] <= j) {
                    store[i][j] = Math.max(
                        values[i-1] + store[i-1][j - weight[i-1]],
                        store[i-1][j]
                        );    
                } else {
                    // Just exclude the last element
                    store[i][j] = store[i-1][j];
                }
            }
        }

        return store[len][W];
    }

    public static void main(String[] args) {
        int val[] = {60, 100, 120}; 
        int wt[] = {10, 20, 30}; 
        int  W = 50; 

        System.out.println(solve(W, wt, val));
    }
}