
/**
 * Given an array of `n` items and a number `K`, find a subarray with sum equal to K
 */

/*
Example:
n = 5
k = 16
arr = {2,4,5,3,7}

Output:
7 5 4
*/

/*
Reasoning

Initial State
     1, 2, 3....K
sum  0  0  0....0
last 0  /  /..../

*/

public class Test {

    public static void findSubarray(int arr[], int K) {
        int len = arr.length; 
        int sum[] = new int[10000];
        int last[] = new int[10000];
        
        for(int i = 0; i <= K; i++)  {
            sum[i] = 0; 
            last[i] = 0;
        }
        last[0] = 0;
        int i;
        for( i = 0; i < len; i++) {
            // Did we reach K ? 
            if(sum[K] == K) break;
            for(int j = 0; j <= K; j++) {
                if(sum[j] == j && last[j] < i + 1 && sum[j + arr[i]] == 0) {
                    sum[j + arr[i]] = j + arr[i];
                    last[j + arr[i]] = i + 1;  
                }
            }
        }
        
        printSolution(arr, last, K);
    }

    public static void printSolution (int arr[], int last[], int K) {
        if(K != 0) {
            System.out.println(arr[last[K] - 1]);
            printSolution(arr, last, K - arr[last[K] - 1]);
        }
    }

    public static void main(String[] args) {
        int arr[] = {2,4,5,3,7};
        int K = 16;
        findSubarray(arr, K);
    }
}