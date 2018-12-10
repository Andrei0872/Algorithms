

// https://www.geeksforgeeks.org/palindromic-tree-introduction-implementation/

/**
 ** Here are just my notes that help me understand this algorithm
 * 
 * Suffix Edge - maximum suffix except the complete string
 * 
 * Root1 - dummy node that describes a string for length - 1
 *       - has a suffix edge connected to itself as for any imaginary string of len -1
 * 
 * Root2 - node which describes a null string of length 0
 * 
 * Insertion of (k+1)th means insertion of a node that is longest palindrome ending at index k+1
 * ( ‘s[k+1]’ + “X” + ‘s[k+1]’ )
 * 
 * To insert k+1 we need to find a string X  =new node=>  s[k+1]+X+s[k+1]
 * To track the node with string X ==> move down the suffix link for the current node (node that contains the insertion of s[k])
 * To find the node that contains the string X we will place the k=1 ch at the end of every node that lies in suffix link chain
 * and also check the first ch
 * 
 * Once inserted the new node, we need to connect it with its suffix child ==>
 *  iterate from node X to find some new string Y such that s[k+1] + Y + s[k+1] is a largest palindromic suffix for the 
 * newly created node
 * 
 */

/*
Example:
str = "abcbab";

Output:
1: a
2: b
3: c
4: bcb
5: abcba
*/
public class Test {

    static int ALPHABET = 26;
    static int MAXN = 1000;
    Node root1, root2; 
    public Node tree[] = new Node[MAXN];
    public int currNode = 0;
    public int ptr; 
    public String str = "";

    class Node {
        int start, end, length;
        // Store insertion for A-Z
        int insertEdge[] = new int[ALPHABET];
        // Store the Maximum Palindromic Suffix for the current Node(excluding the node)
        int suffixEdge; 

        Node() {
            for(int i = 0; i < ALPHABET; i++)
                insertEdge[i] = -1;
        }
    }   

    public void insert(int index) {
        // Search for string X such that str[index] X str[index] is the max palindrome ending at pos index
        int temp = currNode;
        while(true) {
            int currLength = tree[temp].length;
            if(index - currLength >= 1 && str.charAt(index) == str.charAt(index - currLength -1)) 
                break;
            temp = tree[temp].length;
        }

        if(tree[temp].insertEdge[str.charAt(index) - 'a'] != -1) {
            // str[index] X str[index] - already exists
            currNode = tree[temp].insertEdge[str.charAt(index) - 'a'];
            return;
        }

        // Creating a new node
        ptr++;
        tree[ptr] = new Node();

        // Add as a child
        tree[temp].insertEdge[(int) str.charAt(index) - (int)'a'] = ptr;
        tree[ptr].length = tree[temp].length + 2;
        tree[ptr].end = index;
        tree[ptr].start = index - tree[ptr].length + 1;

        // Setting Suffix Edge for the newly created Node

        temp = tree[temp].suffixEdge;
        currNode = ptr;
        if(tree[currNode].length == 1) {
            // Palindrome's length is 1
            // its suffix link to be null
            tree[currNode].suffixEdge = 2; // 2 - basically root2
            return;
        }

        while(true) {
            int currLength = tree[temp].length;
            if(index - currLength >= 1 && str.charAt(index) == str.charAt(index - currLength - 1)) 
                break;
            temp = tree[temp].suffixEdge;
        }
        
        // Now we have found Y
        tree[currNode].suffixEdge = tree[temp].insertEdge[str.charAt(index) - 'a'];
    }

    Test() {
        this.root1 = new Node();
        this.root2 = new Node();

        root1.length = -1;
        root1.suffixEdge = 1;
        root2.length = 0;
        root2.suffixEdge = 1;

        tree[1] = root1;
        tree[2] = root2;
        ptr = 2;
        currNode = 1;

        str = "abcbab";
        int len = str.length();

        int res = str.charAt(0) - 'a';
        System.out.println(res);

        for(int i = 0; i < len; i++)
            this.insert(i);
        
        for (int i=3; i<=ptr; i++) 
        { 
            System.out.print(i - 2 + ": ");
            for (int j=tree[i].start; j<=tree[i].end; j++) 
                System.out.print(str.charAt(j));
            System.out.print('\n'); 
        }
        
    }

    public static void main(String[] args) {
        Test t = new Test();
    }    

}