// Written at: 3 oct 2018

// https://www.geeksforgeeks.org/solve-dynamic-programming-problem/

#include<iostream>
#define NMAX 100
using namespace std;

//* State = set of params that can uniquely identify a certain position or standing in the given problem

// DP is all about using calculated results to formulate the final result

//* Sample Problem
/**
 * Given 3 numbers {1,3,5}, tell the total number
 * of ways we can form a number 'n' using the sum of the given 3 numbers
*/

/*
Total number of ways to form 6 is: 8
1+1+1+1+1+1
1+1+1+3
1+1+3+1
1+3+1+1
3+1+1+1
3+3
1+5
5+1
*/

//* Identifying the state
/*
take param "n" to decide state as it can uniquely identify any subproblem
our state : state(n) - which means, the total number of arrangements to form n by 
using {1,3,5} as elements
*/


//* Reasoning
/*
We can only use 1,3 or 5 to form a given number
Assume theat we know the result for n = 1,2,3,4,5,6;
Let's also assume that we know the result for the state(n=1), state(n=2)... state(n=6)
! We need now the result of state(n=7)
We can only add 1,3 or 6

1) Adding 1 to all possible combinations of state (n = 6)
Ex : 

[ (1+1+1+1+1+1) + 1]
[ (1+1+1+3) + 1]
[ (1+1+3+1) + 1]
[ (1+3+1+1) + 1]
[ (3+1+1+1) + 1]
[ (3+3) + 1]
[ (1+5) + 1]
[ (5+1) + 1] 

------------------------

2) Adding 3 to all possible combinations of state (n = 4);

Ex : 

[(1+1+1+1) + 3]
[(1+3) + 3]
[(3+1) + 3] 


---------------------------


3) Adding 5 to all possible combinations of state(n = 2)
Ex : 
[ (1+1) + 5]


? Therefore
state(7) = state(6) + state(4) + state(2)
OR
state(7) = state(7-1) + state(7-3) + state(7-5)
*/

//* Returns the number of arrangements to form 'n'

// Initialize to -1
int dp[NMAX];

// Use memoization
int solve(int n) {
    if(n < 0)
        return 0;
    // Found one solution!
    if(n == 0)
        return 1;
    
    if(dp[n] != -1 )
        return dp[n];
    return (dp[n] = solve(n - 1) + solve(n - 3) + solve(n-5));
}

int main () {
    for(int i  = 0; i < 100; i++)
        dp[i] = -1;
    
    cout << solve(6) << "\n"; // 8

}