

/* 
Given a number `n`, generate all undirected graphs with `n` nodes
*/

/* 
Example

Input: 
n = 3

Output:

8
0 0 0 
0 0 0 
0 0 0 

0 0 0 
0 0 1 
0 1 0 

0 0 1 
0 0 0 
1 0 0 

0 0 1 
0 0 1 
1 1 0 

0 1 0 
1 0 0 
0 0 0 

0 1 0 
1 0 1 
0 1 0 

0 1 1 
1 0 0 
1 0 0 

0 1 1 
1 0 1 
1 1 0 

*/

#include <iostream>
using namespace std;

int **mat, n, *st;

void print() {
    for(int i = 0, k = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            mat[i][j] = mat[j][i] = st[k];       
            k++;
        }
    }

    for (int i = 0 ; i < n; i++){ 
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "\n";
}

void generate(int k) {
    if(k == n)
        print();
    else {
        for(int i = 0; i <=1; i++) {
            st[k] = i;
            generate(k + 1);
        }
    }
}

void getInput() {
    // cin >> n;
    n = 3;
    mat = new int * [n];
    for(int i = 0; i < n; i++)
        mat[i] = new int[n];
    st = new int[n];
}

int main () {
    getInput();
    
    int m = n * (n - 1) / 2;
    int p = 1;

    for(int i = 1; i <= m; i++)
        p *= 2;
    
    cout << p << '\n';
    generate(0);
    
    return 0;
}
