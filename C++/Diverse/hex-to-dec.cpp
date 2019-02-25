
// Convert hex to decimal

// 1AB --> 427

#include <iostream>
using namespace std;

int convert (char * str, int len, int index = 0) {
    static int result = 0;

    if (index == len)
        return result;
    
    result = result * 16 + (str[index] >= 'A' ? str[index] - 'A' + 10 : str[index] - '0' );

    convert(str, len, index + 1);
}

int main () {
    char str[] = "1AB";
    cout << convert(str, 3);

    return 0;
}