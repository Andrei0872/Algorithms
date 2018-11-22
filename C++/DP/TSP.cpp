
//* Travelling Salesman Problem


#include <iostream>
#include <string>
using namespace std;
#define V 4
#define INF 0x3efefef3

int min(int a, int b) {
    return a < b ? a : b;
}

int solve(int graph[V][V], string str, int temp, int minVal) {
    // Last node
    if(str.length() == 0 ) {
      return graph[temp][0];
    }

    cout << "str : " << str << '\n';
    cout << "temp : " << temp << '\n';

    for(int i = 0; i < str.length(); i++) {
        cout << "graph[temp][str[i]-'0'] " << graph[temp][str[i]-'0']  << '\n';
        minVal = min(
          minVal,
          graph[temp][str[i]-'0'] + solve(graph, str.substr(0, i-0) + str.substr(i+1, str.length() - (i + 1)), str[i] - '0', minVal)
          );
        cout << "minVal: " << minVal << "\n";
    }

    return minVal;
}

int main () {

  int graph[V][V] = { { 0, 10, 15, 20 }, 
                       { 10, 0, 35, 25 }, 
                       { 15, 35, 0, 30 }, 
                       { 20, 25, 30, 0 } }; 
  
  string str = "";
  for(int i = 1; i < V; i++)
      str += to_string(i);
  
  cout << solve(graph,str,0, INF);

}