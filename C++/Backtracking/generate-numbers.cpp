

/**
 * Given a number "n" and a length "lg", generate all the numbers of length "lg"
 * containing n's digits
 */

/*
Example :
    n = 216
    lg = 2

    Output : 11,12,16,21,22,26,61,62,66
*/

#include <iostream>
using namespace std;

int n,lg;
int digits[10];

void determine_digits(int n) {
    while(n) {
        digits[n%10] = 1;
        n /= 10;    
    }
}

void back(int k, int final_num ) {
    if(k == lg + 1) {
        cout << final_num << " "; 
    }else {
        for(int digit = 0; digit < 10; digit++) {
            // If the given number contains the current digit
            if(digits[digit])
                back(k + 1,final_num *10 + digit);
        }
    }
}

int num;
void back2(int k ){
    if(k == lg + 1) {
        cout << num << " "; 
    }else {
        for(int digit = 0; digit < 10; digit++) {
            // If the given number contains the current digit
            if(digits[digit]) {
                num = num * 10 + digit;
                back2(k+1);
                num /= 10;
            }
                
        }
    }
}

int main () {

    cin >> n >> lg;
    determine_digits(n);
    back(1, 0);
    cout << "\n";
    back2(1);
}