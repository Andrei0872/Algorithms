
package graph;
import java.util.LinkedList;
/**
 * 
 * Given a graph, determine if it is acyclic
 * 
 */

public class Graph_Cycle {
	
	int V;
	int cycles;
	int limit;	
	LinkedList<Integer> adj[];
	
	// Constructor
	@SuppressWarnings("unchecked")
	public Graph_Cycle(int _V, int limit) {
		this.V = _V;
		this.cycles = 0;
		this.limit = limit;		
		adj = new LinkedList[this.V];
		for(int i = 0; i < this.V ;i++)
			adj[i] = new LinkedList<>();
	}
	
	public void addEdge(int v, int w) {
		this.adj[v-1].addLast(w-1);
		this.adj[w-1].addLast(v-1);
	}
	
	public boolean solve() {
		
		int[] cycle = new int[this.V];
		int[] color = new int[this.V];
		int[] parent = new int[this.V];
		
		for(int i = 0; i < this.V; i++)
			parent[i] = color[i] = cycle[i] = 0;
		
		this.back(0,-1,color,parent,cycle);
		
//		System.out.println(this.cycles); // 1
		
		return this.is_acyclic(cycle) ? true : false;
//		return true;
	}
	
	@SuppressWarnings("unchecked")
	public boolean is_acyclic(int [] cycle) {
		
		LinkedList<Integer>cycles [] = new LinkedList[this.V];
		
		for(int i =0; i < this.V ;i++)
			cycles[i] = new LinkedList<>();
		
		for(int n = 0; n < this.V; n++) {
			if(cycle[n] != 0) {
				cycles[cycle[n]].addLast(n);
			}
		}
		
		for(int c = 1; c <= this.cycles; c++) {
			if (cycles[c].size() == this.limit) {
				return true;
			}
				
		}
		
		return false;
	}
	
	public void back(int node, int parentOfNode, int[] color, int[] parent, int [] cycle) {
		
		// If the current node has been visited more than twice
		if(color[node] == 2) {
			return;
		}
		
		// If the node has been visited once
		if(color[node] == 1) {
			
			// Found a new cycle
			this.cycles++;
			cycle[parentOfNode] = this.cycles;
			int currentNode = parentOfNode;
			
			// Add to the cycle the other adjacent nodes
			while(currentNode != node) {
				currentNode = parent[currentNode];
				cycle[currentNode] = this.cycles;
			}
			
			return;
		}
		
		// Mark this as visited once
		color[node] = 1;
		// Set the parent
		parent[node] = parentOfNode;
		
		// Loop through the adjacent nodes of the current node
		for(Integer adjNode : this.adj[node] ) {
			// Avoid the parent
			if(adjNode == parent[node]) continue;
			this.back(adjNode, node, color, parent, cycle);
		}
		
		// Mark the current node as visited twice
		color[node] = 2
	
	public static void main(String[] args) {
		Graph_Cycle g = new Graph_Cycle(7,4);
		g.addEdge(1, 2);
		g.addEdge(2, 3);
		g.addEdge(3, 4);
		g.addEdge(1, 4);
		g.addEdge(6, 5);
		g.addEdge(5, 2);
		String res = g.solve() ? "yes" : "no";
		System.out.println(res);
	
		Graph_Cycle g2 = new Graph_Cycle(4,4);
		g2.addEdge(1, 2);
		g2.addEdge(4, 3);
		g2.addEdge(2,3);
		String res2 = g2.solve() ? "yes" : "no";
		System.out.println(res2);
	
		Graph_Cycle g3 = new Graph_Cycle(7,4);
		g3.addEdge(1, 2);
		g3.addEdge(2, 3);
		g3.addEdge(3, 4);
		g3.addEdge(5, 4);
		g3.addEdge(6, 5);
		g3.addEdge(5, 1);
		String res3 = g3.solve() ? "yes" : "no";
		System.out.println(res3);
	
	}

}

