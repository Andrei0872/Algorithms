

/**
 * Given a number "n", generate all the possible combinations where the number "n"
 * can be written as a sum of distinct unsingned digits
*/

/*
Example 
N = 12

1 2 3 6
1 2 4 5
1 2 9
1 3 8
1 4 7
1 5 6
etc..
*/

#include <iostream>
using namespace std;
const int N = 12;
int solutions;
int st[10];

// Make sure that the digit that it is about to be added hasn't been encountered 
// before into the current solution & the current digit is the greater
bool valid(int k,int digit) {

    for(int i = 0; i <k; i++) 
        if(st[i] == digit || st[i] > digit) return false;
    
    return true;
}

void back(int k, int sum) {

    if(sum == N) {

        cout << "solution :  " << ++solutions << "\n";
        for(int i = 0; i <k; i++)
            cout << st[i] << " ";
        
        cout << "\n";
    } else {
        // Elements are from 1 to N - 1
        for(int i = 1; i <= N-1;i++) {
            if(valid(k,i)) {
                st[k] = i;
                sum += i;
                back(k+1,sum);
                // Backtrack
                sum -= i;
            }
        }
    } 

}

int main () {
    back(0,0);
    return 0;
}
