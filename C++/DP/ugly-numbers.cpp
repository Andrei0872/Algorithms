
// Given a number  "n", find the n-th Ugly number

// Ugly numbers  : numbes whose only primme factors are 2,3 or 5;
// Sequence : 1, 2, 3, 4, 5, 6, 8, 9, 10, 12, 15

/*
Reasoning : {
    - every number can only be divided by 2,3 or 5
    - we can split the sequence this way :{
         1×2, 2×2, 3×2, 4×2, 5×2, …
         1×3, 2×3, 3×3, 4×3, 5×3, …
         1×5, 2×5, 3×5, 4×5, 5×5, …
    }
    - by conventionm, the sequnce starts with 1 : ugly[0] = 1
    - we'll use 3 indices : i2,i3,i5 
    - on every iteration we will  get the next ugly number as min(multyple_2,multyple_3,multyple_5)
    - if the ugly number === multyple_2 || multyple_3 || multyple_5
    - increment the corresponding index
    - update the multyple_x 
}
*/

#include <iostream>
using namespace std;

int min_value(int x, int y, int z) {
    return x < y ? x < z ? x : z  : z < y ? z : y;
}

unsigned solve(unsigned n) {

    unsigned ugly[n],
        i2 = 0, i3 = 0, i5 = 0,
        multiple_of_2 = 2,
        multiple_of_3 = 3,
        multiple_of_5 = 5,
        ugly_number = 1;

    // Convention
    ugly[0] = 1;

    for(int i =1; i<n;i++) {
        ugly_number = min_value(multiple_of_2,multiple_of_3,multiple_of_5);
        ugly[i] = ugly_number;

        if(ugly_number == multiple_of_2 ) {
            i2++;
            multiple_of_2 = ugly[i2] * 2;
        } 
        if(ugly_number == multiple_of_3) {
            i3++;
            multiple_of_3 = ugly[i3] * 3;
        } 
        if(ugly_number == multiple_of_5) {
            i5++;
            multiple_of_5 = ugly[i5] * 5;
        }

    }

    return ugly_number;
}

int main () {   

    cout << solve(8) << "\n"; // 9
    cout << solve(10) << "\n"; // 12
    cout << solve(150) << "\n"; // 5832

}