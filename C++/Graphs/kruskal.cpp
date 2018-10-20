
// Minimum Spanning Tree

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

int V, *parent;

vector<pair<int,pair<int,int> > > adj; 
vector<pair<int,int> > result;

// Getting input
void test1() {
    int cost, n1, n2;
    ifstream f("date.in");
    f >> V;
    parent = new int[V];
    while(!f.eof()) {
        f >> cost >> n1 >> n2;
        adj.push_back(make_pair(cost,make_pair(n1,n2)));
    }

    f.close();
}

int find(int node) {
    if(node != parent[node]) {
        parent[node] = find(parent[node]);
    }
    return parent[node];
}

void solve() {
    int first,second, currentCost, finalCost = 0;
    for(int i = 0; i < V; i++)
        parent[i] = i;

    sort(adj.begin(), adj.end());

    for(auto elem : adj) {
        currentCost = elem.first;
        first = elem.second.first;
        second = elem.second.second;

        // If the 2 nodes don't have the same parent
        if(find(first) != find(second)) {
            finalCost += currentCost;
            result.push_back({first,second});
            parent[parent[second]] = parent[first];
        }
    }

    cout << finalCost << "\n";

    for(auto elem : result) {
        cout << elem.first << " " << elem.second << "\n";
    }    

    for(int i = 0; i < V; i++) 
        cout << parent[i] << " ";

}

int main () {
    test1();
    solve();
    return 0;
}