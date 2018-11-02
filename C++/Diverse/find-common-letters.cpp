

// Find common letters of 2 strings

#include <iostream>
#include <cstring>
using namespace std;

void commonLetters(char s1[], char s2[]) {

    // Use 2 vector to count the occurrences
    int *fr1 = new int[26];
    int *fr2 = new int[26];

    // First string
    for(int i  = 0; i < strlen(s1);i++) {
        // ~undefined = -1
        // ~1 = -2; -~1 = 2 and so on..
        fr1[s1[i] - 97] = -~fr1[s1[i] - 97];
    }

    // Second string
    for(int i  = 0; i < strlen(s2);i++) {
        fr2[s2[i] - 97] = -~fr2[s2[i] - 97];
    }

    for(int i =0; i <= 25;i++) {
        // If there is a common letter
        if(fr1[i] && fr2[i]) {
            cout << char(i + 97) <<" ";
        }
    }
}

int main (){
    
    char s1 [] = "asdajdasm" ;
    char s2 [] = "dasmkmkqsk";
    commonLetters(s1,s2); // a d m s
    return 0;
}   