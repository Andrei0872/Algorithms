

/*
Example : 
s1 = 7145
s2 = 837845

Output : 7 5
*/

#include <iostream>
#include <string>
#define NMAX 201
using namespace std;

string s1,s2;
bool found;
int lcs[NMAX][NMAX];

int max(int n1, int n2) {
    return n1 > n2 ? n1 : n2;
}

void getInput() {
    cin >> s1 >> s2;
}

void test() {
    s1 = "7135";
    s2 = "837845";
}

void visualizeMatrix() {

    for(int i = 0; i <= s1.length(); i++) {
        for(int j = 0; j <= s2.length(); j++) {
            cout << lcs[i][j] << " "; 
        }
        cout << "\n";
    }

}

void determineLCS() {

    int l1 = s1.length(),
        l2 = s2.length();

    // We will need to start from 0 in case the first 2 letters from both match
    s1.insert(0," ");
    s2.insert(0," ");

    for(int i = 1; i <= l1; i++) {
        for(int j = 1; j <= l2; j++)
            if(s1[i] == s2[j]) {
                lcs[i][j] = lcs[i-1][j-1] + 1; 
                found = true;
            }else {
                // Always get the max value
                lcs[i][j] = max(lcs[i-1][j],lcs[i][j-1]);
            }
    }

    // visualizeMatrix();
    cout << lcs[l1][l2] << "\n";
}

void printLCS(int x, int y) {
    // Base case
    if(!x || !y)
        return;
    if(s1[x] == s2[y]){
        printLCS(x-1,y-1);
        cout <<  s1[x] << " ";
    } else if(lcs[x][y] == lcs[x-1][y])
        printLCS(x-1,y);
    else printLCS(x,y-1);
}

int main () {
    
    // getInput();
    test();
    determineLCS();
    if(!found) {
        cout << "There is no common sequence";
    } else {
        printLCS(s1.length()-1,s2.length()-1);
    }
    return 0;
}
