
package graphs;

import java.util.LinkedList;

/**
 * Given a graph, determine if it is Hamiltonian
 * 
 * Example : {
 * 
 * V = 5, E = 6
 * 1 2
 * 3 4
 * 2 4
 * 4 5 
 * 5 3 
 * 3 1
 * 
 * OUTPUT : 0 1 3 4 2 0
 * 
 * }
 * 
 * */

public class PrintHamiltonian {
	
	static int path[];
	
	static class Graph {
		int v;
		LinkedList<Integer> adj[];
		
		@SuppressWarnings("unchecked")
		Graph(int V) {
			this.v = V;
			adj = new LinkedList[V];
			for(int i =0; i < V; i++) {
				adj[i] = new LinkedList<>();
			}
		}
	}
	
	static void addEdge(Graph g, int v, int w) {
		g.adj[v-1].addLast(w-1);
		g.adj[w-1].addLast(v-1);
	}
	
	static boolean isSafe(Graph g, int currentNode, int pos) {
		
		// Check if this current node is adjacent with the previous node
		boolean found = false;
		for(Integer adj : g.adj[path[pos-1]]) {
			if (adj == currentNode)
				found = true;
		}
		if(found == false)
			return false;

		// Check if the current node has already been added
		for(int i =0; i < pos ; i++)
			if(path[i] == currentNode)
				return false;
		
		return true;
	}
	
	static boolean hamCycle_util (Graph g, int pos) {
		
		// Base case
		if(pos == g.v) {
			
			// Check if a cycle has been found
			// Last node == First node
			if(g.adj[path[pos-1]].contains(path[0])) {
				return true;
			}else {
				return false;
			}
			
		}
		
		for(int v = 1; v < g.v; v++) {
			if(isSafe(g, v, pos)) {
				path[pos] = v;
				
				if(hamCycle_util(g, pos + 1) == true) {
					return true;
				}
 				
				// Remove from cycle
				path[pos] = -1;
				
			}
		}
		
		// If no vertex could be added
		return false;
		
	}
	
	static void hamCycle(Graph g) {
		
		path = new int[g.v];
		for(int i =0; i < g.v; i++)
			path[i] = -1;
		
		// Star from the first vertex as it doesn't really matter the order since this is an undirected graph
		path[0] = 0;
		
		if(hamCycle_util(g, 1) == false) {
			System.out.println("There is no solution");
			return;
		}
		
		
		printCycle(g);
		
	}
	
	static void printCycle(Graph g) {
		
		for(int i =0; i < g.v; i++)
			System.out.print(path[i] +" ");
		
		// Print the first node in order to show the complete cycle
		System.out.println(path[0]);
		
	}
	
	public static void main(String[] args) {
		Graph g = new Graph(5);
		addEdge(g, 1, 2);
		addEdge(g, 3, 4);
		addEdge(g, 2, 4);
		addEdge(g, 4, 5);
		addEdge(g, 5, 3);
		addEdge(g, 3, 1);
	
		hamCycle(g);
		
	}
	
}
