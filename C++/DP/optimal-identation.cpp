
/**
 * Given N words, print them with an optimal indentation and determine the cost.
 * That means :
 * a) On each line there must be no more than M characters
 * b) The order of the given sequence of words stays unchanged
 * c) Between 2 words there must be only one whitespace
 * d) On each line there will be only unseparated words
 * 
 * The cost : 
 * S1,S2,S3,...,Sp - number of white spaces left on every line, except the last one
 * The cost is : S1^3 + S2^3+...+Sp^3
 */

#include <fstream>
#include <cstring>
#define InFile "text.in"
#define OutFile "text.out"
#define NMAX 101
#define MMAX 51
#define p3(x) ((x) * (x) * (x))
using namespace std;

int N, M;
// slen - slg[i] - sum of words' 1,2,3...i length
int slen[NMAX];
// cost - cost[i] - the cost of the indentation of the N words
long cost[NMAX];
// The words
char words[NMAX][NMAX];
// last[i] - last word put on the line where there is the word "i"
long last[NMAX];



void getInput() {
    ifstream fin(InFile);
    int i;
    fin >> N >> M;
    fin.get();
    for(i = 1; i <= N; i++) {
        fin.getline(words[i],NMAX);
        // Also determine the sum of the words' length
        slen[i] = slen[i-1] + strlen(words[i]);
    }
    fin.close();
}

void solve() {
    int i,j;
    // At first there is no cost
    cost[N] = 0;
    last[N] = N;

    for(int i = N - 1; i > 0;i --) {
        // Do the words fit on a single line ? 
        if(slen[N] - slen[i-1] + N - i <=M) {
            cost[i] = 0;
            last[i] = N;
        } else {
            // Also add the previous cost
            cost[i] = p3(M - slen[i] + slen[i-1]) + cost[i + 1] ;
            // At the moment, the word "i" is the last one on the line "i"
            last[i] = i; 
            // Could there be more than one word on a single line ? 
            for(j = i + 1;j < N; j++){
                // Check if they fit
                if(slen[j] - slen[i-1] + j - i > M)
                    break;
                long val = cost[j + 1] + p3(M - (slen[j] - slen[i-1] + j - i) ) ;
                if(cost[i] > val ) {
                    cost[i] = val;
                    // "j" is the last word on the line
                    last[i] = j;
                }
            }
        }
    }
}

void printText() {
    ofstream fout(OutFile);
    int pos = 0;
    fout << cost[1] << "\n";

    while(pos + 1 <= N) {
        for(int i = pos + 1; i < last[pos + 1];i++)
            fout << words[i] << " ";
        fout << words[last[pos + 1]] << "\n";
        pos = last[pos + 1];
    }
    fout.close();
}

int main () {

    getInput();
    solve();
    printText();

    return 0;
}

// Example
/*
text.in
17 15
A
fost
odata
ca-n
povesti
a
fost
ca
niciodata
din
rude
mari
imparatesti
o 
prea
frumoasa
fata
*/

/*
text.out
503
A fost odata
ca-n povesti
a fost ca
niciodata
din rude mari
imparatesti o 
prea frumoasa
fata

*/