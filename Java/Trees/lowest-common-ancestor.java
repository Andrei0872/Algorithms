

package trees;

import java.util.HashMap;
import java.util.Map;

//Lowest Common Ancestor in a Binary Tree - Using parent pointer 

//https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-tree-set-2-using-parent-pointer/

/**
* Given values of two nodes in a Binary Tree, find the Lowest Common Ancestor
* 
* Reasoning for the first solution : {
*  1) Create a hash table
*  2) Insert the first node and its ancestors
*  3) Check if either the second node or one of its ancestors are in the hash tables
* }
* 
*/

// Node structure
class Node {
	int val;
	Node parent, left,right;
	Node(int val) {
		this.val = val;
		parent = left = right = null;
	}
}


public class BinaryTreee {
	
	Node root, n1, n2;
	Node insert(Node currentNode,int value) {
		
		// If the tree has not been initialized
		if(currentNode == null) return new Node(value);
		
		if(value < currentNode.val) {
			// Left 
			currentNode.left = insert(currentNode.left, value);
			currentNode.left.parent = currentNode;
		} else if(value > currentNode.val) {
			// Right
			currentNode.right = insert(currentNode.right, value);
			currentNode.right.parent = currentNode;
		}
		return currentNode;
	}
	
	public int LCA(Node n1, Node n2) {
		
		// Create Hash Table
		Map<Node, Boolean> ancestors = new HashMap<Node, Boolean>();
		
	    // Store for the first node
		while(n1 != null) {
			ancestors.put(n1,Boolean.TRUE);
			n1 = n1.parent;
		}
		
	    // Check if the second node or one of its ancestors are already in the hash table
		while(n2 != null) {
			if(ancestors.containsKey(n2) != ancestors.isEmpty()) {
				return n2.val;
			}
			n2 = n2.parent;
		}
		return -1;
	}

	// Find depth for a given graph
	public int depth(Node n) {
		int d = -1;
		while(n != null) {
			d++;
			n = n.parent;
		}
		return d;
	}
	
	 /**
	  * Find depths of given nodes, move up to the deeper node by the diff between the 2 nodes 
	  * Once both nodes reach the same level, traverse them up and return the common node
	  * 
	  */
	public int LCA2(Node n1, Node n2) {
		int d1 = this.depth(n1),
			d2 = this.depth(n2);
		int diff = d1 - d2;
		
		// If n2 is deeped than n1, swap n1 and n2
		if(diff < 0) {
			Node temp = n1;
			n1 = n2;
			n2 = temp;
			diff = -diff;
		}
		
		// Get n1 and n2 at the same level
		while(diff-- != 0 ) {
			n1 = n1.parent;
		}
		
		// Now, n2 and n1 are on the same level
		while(n1 != null && n2 != null) {
			if(n1 == n2)
				return n1.val;
			n1 = n1.parent;
			n2 = n2.parent;
		}
		
		return -1;
	}
	
	public static void main(String[] args) {
		
		BinaryTreee tree = new BinaryTreee();
		
	 	tree.root = tree.insert(tree.root, 20); 
        tree.root = tree.insert(tree.root, 8); 
        tree.root = tree.insert(tree.root, 22); 
        tree.root = tree.insert(tree.root, 4); 
        tree.root = tree.insert(tree.root, 12); 
        tree.root = tree.insert(tree.root, 10); 
        tree.root = tree.insert(tree.root, 14); 
	
		
		tree.n1 = tree.root.left.right.right; // 14
		tree.n2 = tree.root.left.left; // 4
		
		int lca = tree.LCA(tree.n1, tree.n2);
		int lca2 = tree.LCA2(tree.n1, tree.n2);
		System.out.println(lca);
		System.out.println(lca2);
		
	}
	
}

