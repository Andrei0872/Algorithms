
/*
Given a number x from a file date.in
Generate all the combinations of "x" length such that there is no st[i], st[i+1] !=0
A combination will contain digits from 0 to x - 1
*/

/*
Example: 
x = 3   

Output :  
(0 0 0),(0 0 1),(0 1 0),(1 0 0),(1 0 1) 
*/

#include <iostream>
#include <fstream>
using namespace std;
int x;
int st[10];

void getInput() {
    ifstream f("date.in");
    f >> x;
    f.close();
}

bool valid(int k, int digit ) {
    if(st[k-1] != 0 && digit != 0 )
        return false;
    
    return true;
}

void print() {
    for(int i =0; i < x; i++)
        cout << st[i] << " ";
    cout << "\n";
}

void back(int k) {
    
    // Base case
    if(k == x ) {
        print();
    } else {
        for(int i =0; i < x-1; i++) {
            if(valid(k,i)) {
                st[k] = i;
                back(k + 1);
            }
        }
    }

}

int main () {
    getInput();
    back(0);
    return 0;
}