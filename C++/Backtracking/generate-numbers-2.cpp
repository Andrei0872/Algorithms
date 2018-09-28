

// Given a number "n", generate all the numbers formed by odd digits and with the 
// first letter being the same as the last letter

/*
Example : 
N = 3

Output :
111
131
151
171
191
313
333
353
etc..
*/

#include <iostream>
using namespace std;
int N;
int st[10];
int solutions;

void back(int k) {
    if(k == N) {
        if(st[k-1] == st[0]) {
            cout << "solution :  " << ++solutions << "\n";
            for(int i =0; i<N;i++)
                cout << st[i];
        
             cout << "\n";
        }
        return;
    }else {
        for(int i = 1; i<=9; i++) {
            if(i % 2 != 0) { 
                st[k] = i; 
                back(k+1);
            }
        }
    }
}

int main () {
    cin >> N;
    back(0);
    return 0;
}
