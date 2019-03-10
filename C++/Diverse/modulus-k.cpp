
/* 
Given 3 numbers, `i`, `j` and `k`, calculate (i ^ j) % k

Example:
(100 ^ 100) % 7 = 2
(125 ^ 199) ^ 998 = 800
(2 ^ 10) % 9 = 7

Reasoning:
- i = 2, j = 10, k = 9

while (j) {};

i
2 ^ 1 % 9 = 2(= r1), j = 10
2 ^ 2 % 9 = r1 * i % k = 2 * 2 % 9 = 4(= r2), j = 9
2 ^ 3 % 9 = r2 * i % k = 4 * 2 % 9 = 8(= r3), j = 8
2 ^ 4 % 9 = 8 * 2 % 9 = 7(= r4), j = 7
2 ^ 5 % 9 = 7 * 2 % 9 = 5(= r5), j = 6
2 ^ 6 % 9 = 5 * 2 % 9 = 1(= r6), j = 5
2 ^ 7 % 9 = 1 * 2 % 9 = 2(= r7), j = 4
2 ^ 8 % 9 = 2 * 2 % 9 = 4(= r8), j = 3
2 ^ 9 % 9 = 4 * 2 % 9 = 8(= r9), j = 2
2 ^ 10 % 9 = 8 * 2 % 9 = 7(= r10), j = 1
j = 0 => return r10(7)

*/

#include <iostream>
using namespace std;

int solve (int i, int j, int k) {

    if (j == 0)
        return 1;

    int result = i % k;

    while (--j) {
        result = (result * i) % k;
    }

    return result;
}

int main () {
    cout << solve(2, 10, 9) << '\n'; // 7
    cout << solve(125, 199, 999) << '\n'; // 800
    cout << solve(100, 100, 7) << '\n'; // 2
    cout << solve(8, 0, 100) << '\n'; // 1
    cout << solve(5, 151, 5) << '\n'; // 0

    return 0;
}