

// Cartesian Product of a given array

/*
Array : {1,2,3} 
Output : 
{1 1 1}
{1 1 2}
{1 1 3}
{1 2 1}
{1 2 2}
{1 2 3}
.
.
.
*/


#include <iostream>
using namespace std;
int st[10];
int arr[30], n;

void getInput() {
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
}

void print(int k) {
    for(int i = 0; i < k; i++)
        cout << st[i] << " ";
    cout << "\n";
}

void back(int k) {
    // Base case
    if(k == n )
        print(k);
    else {
        for(int i = 0; i < n; i++) {
            st[k] = arr[i];
            back(k+1);
        }
    }
}

int main () {
    getInput();
    back(0);
    return 0;
}