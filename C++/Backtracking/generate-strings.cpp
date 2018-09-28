
// Given a number "n" genereate all the strings such that 
// there are not 2 A letters next to each other

/*
Example 
n = 3

Output : 
AMA
AMM
MAM
MMA
MMM
*/

#include <iostream>
using namespace std;
char letters[2] = {'A','M'};
const int N = 3;
char st[N];

bool valid(int k, char letter) {
    return st[k-1] == 'A' && letter == 'A' ? false : true; 
}

void afisare() {
    for(int i =0; i < N;i++)
        cout << st[i];

    cout << "\n";
}

void back(int k) {

    if(k == N) {
        afisare();
    }else {
        for(int l = 0; l < 2; l++) {
            if(valid(k,letters[l])) {
                st[k] = letters[l];
                back(k+1);
            }   
        }
    }
}

int main () {
    back(0);
    return 0;
}

