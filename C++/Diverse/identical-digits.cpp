
/* 
Given 2 numbers `a` and `b`, determine the numbers within the interval [a, b]
with identical digits
*/

#include <iostream>
using namespace std;
#define MAXNUM 1000

bool identicalDigits (int num) {
    if (num < 10) 
        return true;
    
    if (num > 9 && num < 100)
        return num % 10 == num / 10;

    int lastDigit = num % 10;
    num /= 10;

    while (num) {
        if (num % 10 != lastDigit)
            return false;

        num /= 10;
    }

    return true;
}

void solve (int a, int b) {
    int result[MAXNUM] = { 0 };
    int result_len = 0;

    for (int num = a; num <= b; num++ )
        if (identicalDigits(num)) 
            result[result_len++] = num;

    if (result_len) {
        cout << result_len << '\n';

        for (int i = 0; i < result_len; i++)
            cout << result[i] << ' ';
    } else {
        cout << "no results \n";
    }
}

int main () {

    // solve(8, 120); // 8 9 11 22 33 44 55 66 77 88 99 111
    solve(590, 623); // No results

    return 0;
}