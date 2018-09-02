
package graphs;

import java.util.LinkedList;


public class PrintGraph {

	
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
		g.adj[v].addLast(w);
		g.adj[w].addLast(v);
	}
	
	static void printGraph(Graph g) {
		for(int node = 0; node < g.v; node++) {
			if(g.adj[node].isEmpty()) continue;
			System.out.println("head : " + node + ":");
			for(Integer adj : g.adj[node]) {
				System.out.print(adj + " ");
			}
			System.out.println("\n");
		}
	}
	
	public static void main(String[] args) {
		
		int V = 5;
		Graph g = new Graph(V);
		addEdge(g, 0, 1);
		addEdge(g, 0, 4);
		addEdge(g, 1, 2);
		addEdge(g, 1, 3);
		addEdge(g, 1, 4);
		addEdge(g, 2, 3);
		addEdge(g, 3, 4);
		
		printGraph(g);
		
	}
	
}
