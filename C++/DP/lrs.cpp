
/**
 * Given a string, print its Longest Repeated Subsequence
 */

/*
Example
str = "AABEBCDD"

Output : "ABD"
*/

// The solution is similar to Longest Common Subseque, you only need to find
// LCS(str,str), but with  the restriction that 2 chars cannot be the same
// and also have the same index


#include <iostream>
#include <string>
using namespace std;

int max(int n1, int n2) {
    return n1 > n2 ? n1 : n2;
}

string reverse_str(string str) {
    char temp;
    for(int len = str.length(),i = 0; i < len/2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len-i-1] = temp;
    }
    return str; 
}

string solve(string& str) {

    int len = str.length();
    
    int dp[len+1][len+1];

    // Initialize & Solve
    for(int i = 0;i <= len; i++) {
        for(int j = 0; j <= len; j++) {
            // Borders - top and left
            if(i == 0  || j == 0)
                dp[i][j] = 0;
            else {
                if(str[i-1] == str[j-1] && i != j) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            } 
        }
    }
    for(int i = 0;i <= len; i++) {
        for(int j = 0; j <= len; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "LRS length : " << dp[len][len] << "\n"; 

    string result = "";
    int i = len, j = len;
    while(i !=0 && j != 0) {
        // If this cell is same as diagonally adjacent cell
        if(dp[i][j] == dp[i-1][j-1] + 1) {
            result += str[i-1];
            i--;
            j--;
        } else if(dp[i][j] == dp[i-1][j])
            i--;
          else j --;       
    }

    // Since we traverse dp[][] from bottom
    // we get the result in reverse order
    return reverse_str(result);

}

int main () {
    string str = "AABEBCDD";
    cout << solve(str) << "\n";
    return 0;   
}