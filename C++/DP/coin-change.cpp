

// https://www.geeksforgeeks.org/coin-change-dp-7/

/**
 * Write a function that counts how many ways you can change for that for an amount of money, 
 * given an array of coin denominations.
 * 
 * Example {
 *  1) sum = 4, coins = [1,2]
 *  Output : 3  (1 1 1 1;  1 1 2; 2 2)
 * }
 * 
 */

#include <iostream>
using namespace std;

int cnt(int coins [], int money, int len) {

    int table[money+1][len] = {{0}};

    // Base cases : money == 0 ==> a solution has been found
    for(int i = 0; i < len; i++)
        table[0][i] = 1;

    int x,y;
    for(int i = 1; i <= money; i++) {
        for(int j = 0; j < len; j++) {
            // Include coins[j]
            x = (i - coins[j] >=0 ) ? table[i - coins[j]][j] : 0;
            // Exclude coins[j]
            y = (j >= 1) ? table[i][j-1] : 0;
            table[i][j] = x + y;
        }      
    }

    // Visualize the matrix
    for(int i = 0; i <= money; i++){
        for(int j =0; j < len;j++){
            cout << table[i][j] << " ";
        }
        cout << "\n";
    }

    return  table[money][len-1];
}

// Another approach
int cnt2(int coins[], int money, int len) {

    int table[money+1] = {0};  
    
    // Base case : money == 0
    table[0] = 1;

    for(int i = 0; i < len; i++) {
        int currentElem = coins[i];
        for(int j =currentElem; j <= money; j++) {
            table[j] += table[j - currentElem];
        }
    }

    // Visualize the array
    for(int i =0; i <= money; i++) 
        cout << table[i] << " ";

    return table[money];
}

int main () {
    
    int coins[] = {5,2,3};
    int len = sizeof(coins)/sizeof(coins[0]);
    int money = 10;

    cout << cnt (coins,money,len) << "\n"; // 4
    cout << cnt2 (coins,money,len) << "\n"; // 4

    return 0;
}
