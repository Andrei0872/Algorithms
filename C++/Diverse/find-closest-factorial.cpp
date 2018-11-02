
// Given a number "n", find its closest factorial

 /**
  * Example : {
  *  1) n = 10
 *      Output : 6(3!)
     2)
     n = 22
     Output : 24(4!)
  * }
  * 
  * 
  * Reasoning {
  *  1) Use a function that will determine if its parameter can be written as a factorial
  *  2) Use a function that will take 2 params:
  *      - first param - the number "n"
  *      - second param - 1/-1; this will help us determine the closest factorial
  * }
  * 
 */


#include <iostream>
using namespace std;

bool isFactorial(int n ) {

    int y = 1, i=1;
    
    while(y < n) {
        y *= i; i++;
    }

    return (n == y);
}

// t can either be 1 or -1
int closestFactorial(int n, int t) {
    
    while(!isFactorial(n) && (n > 0)) n += t; 
    return n;

}


int main () {

    int n = 22;
    
    // Get the closest factorial
    // We want to get the min difference
    if(n - closestFactorial(n,-1) < closestFactorial(n,1) - n) {
        cout << closestFactorial(n,-1) << "\n";
    } else {
        cout << closestFactorial(n,1) << "\n"; // 24
    }   
    
    return 0;
}
