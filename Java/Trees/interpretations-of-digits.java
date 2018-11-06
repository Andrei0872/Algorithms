import java.util.Arrays;
/**
 * Finding all possible interpretations of an array of digits
 * 
 * 'a' - represented as 1
 * 'b' - represented as 2
 * .
 * .
 * .
 * 'z' - represented as 26
 * 
 * Given an array of digits (1 to 9) as input, print all valid interpretations
 * 
 */

/*
Example
Input: {1, 2, 1}
Output: ("aba", "au", "la") 
[3 interpretations: aba(1,2,1), au(1,21), la(12,1)]
*/

/**
 * Use a binary tree as we can have 2 paths : single digit & two digits
 * All interpretations will be in leaf nodes
 */

class Node {
    String data;
    Node left, right;

    Node(String _data) {
        this.data = _data;
        left = right = null;
    }

    public String getData() { return this.data; }
}

public class Interpretations {
    private static final String[] alphabet = {"", "a", "b", "c", "d", "e", 
    "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", 
    "s", "t", "u", "v", "w", "x", "v", "z"}; 
    
    public static Node buildTree(int letter, String data, int arr[]) {
        if(letter > 26)
            return null;
        
        String final_result = data + alphabet[letter];
        Node root = new Node(final_result);

        // Did we reach a leaf?
        if(arr.length != 0) {
            letter =  arr[0];
            // Left child -  One digit
            int newArr []= Arrays.copyOfRange(arr,1,arr.length);
            root.left = buildTree(letter, final_result, newArr);

            // Right child - two digits
            if(arr.length > 1) {
                letter = arr[0] * 10 + arr[1];
                newArr = Arrays.copyOfRange(arr,2,arr.length);
                root.right = buildTree(letter, final_result, newArr);
            }   
        }
        return root;
    }

    public static void printResults(Node root) {
        // Beyond the leaf - STOP
        if(root == null)
            return;
        // Did we reach a leaf? 
        if(root.left == null && root.right == null) 
            System.out.println(root.getData());
        printResults(root.left);
        printResults(root.right);
    }

    public static void solve(int arr[]) {
        Node root = buildTree(0, "", arr);
        printResults(root);
    }
    public static void main(String[] args) {
        int[] arr = {1,1,3,4};
        solve(arr);
    }   
}
