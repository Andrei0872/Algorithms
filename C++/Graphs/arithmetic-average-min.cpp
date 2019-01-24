/*
Given a graph, determine the node whose arithmetic average is minimum
*/
/*
Example
5 6
1 2 10
2 3 2
2 5 2
3 5 12
3 4 1
4 5 5
Output : 4
*/

#include <iostream>
#include <fstream>
#include <list>
using namespace std;

list<pair<int, int> > * adj;
int N, M;

void getInput() {
    ifstream f("date.in");
    int v, w, c;
    f >> N >> M;
    
    adj = new list<pair<int, int> >[N];
    
    for(int i = 0; i < M; i++) {
        f >> v >> w >> c;
        adj[v-1].push_back(make_pair(w-1,c));
        adj[w-1].push_back(make_pair(v-1,c));
        
    }
    f.close();
}
void solve() {
    float minAverage = 32000.0;
    int nod = -1;
    
    for(int i = 0; i < N; i++) {
        if(adj[i].size() == 0) continue;
        
        int sum = 0;
        list<pair<int, int> >::iterator it;
        
        for(it = adj[i].begin(); it != adj[i].end(); ++it) {
            sum += (*it).second;
        }
        
        float average = sum / adj[i].size();
        
        if(average < minAverage) {
            minAverage = average;
            nod = i + 1;
        }
    }
    cout << nod;
}

int main () {
    getInput();
    solve();
    return 0;
}