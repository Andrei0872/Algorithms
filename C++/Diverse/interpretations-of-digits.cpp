
// Java Implementation using Binary Tree : https://github.com/Andrei0872/Algorithms/blob/master/Java/Trees/interpretations-of-digits.java

/**
 * Finding all possible interpretations of an array of digits
 * 
 * 'a' - represented as 1
 * 'b' - represented as 2
 * .
 * .
 * .
 * 'z' - represented as 26
 * 
 * Given an array of digits (1 to 9) as input, print all valid interpretations
 * 
 */

/*
Example
Input: {1, 2, 1}
Output: ("aba", "au", "la") 
[3 interpretations: aba(1,2,1), au(1,21), la(12,1)]
*/

/**
 * Use a binary tree as we can have 2 paths : single digit & two digits
 * All interpretations will be in leaf nodes
 */

#include <iostream>
using namespace std;

void solve(char givenArr[], char solution[], int index,int  solution_index,int limit) {
    if(index == limit) {
        solution[solution_index] = '\0';
        cout << solution << '\n';
        return;
    } 

    // 2 digits
    if(index < limit - 1) {
        int offset = (givenArr[index] - '0') * 10 + (givenArr[index+1] - '0');
        if(offset < 26) {
            // letters : 0 ... 25
            solution[solution_index] = char('a' + offset - 1);
            solve(givenArr,solution,index + 2,solution_index +1, limit);
        }
    }

    // 1 digit
    if(givenArr[index] - '0' >= 1) {
        solution[solution_index] = char('a' + givenArr[index] - '0' - 1);
        solve(givenArr,solution, index+1,solution_index  + 1,limit);
    }
}

int main () {
    int limit = 0;
    char test[] = "123";
    char solution[255];
    for(int i = 0; test[i] != '\0'; i++)
        limit++;

    solve(test,solution,0,0,limit);
    return 0;
}