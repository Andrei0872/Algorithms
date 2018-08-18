
// Print all combinations of N elements such that their sum is divisible  by M

/*
Reasoning : {
    1) Use backtracking to generate all the possible combinations
    2) For every array of N elements we verify if their sum is divisible by M
    3) If so, we print them, with their sign
}
*/

#include <iostream>
using namespace std;
 
class Generate {
    int *arr;
    int n; // Array length
    int m;

    // This will help us generate the arrays
    int *st; 

    public:
        Generate(int _n,int _m){
            n = _n;
            arr =new int[n];
            st = new int[n+1];
            m = _m;
            
            // Get the user input
            for(int i = 0; i < n;i++) {
                cin >> arr[i];
            }   
        }

        // Print solution if the the it's correct
        void printSol(){
            int s = 0;
            // If the element is part of the array, we choose "+", otherwise, "-"
            for(int i=0;i < n;i++) {
                if(st[i] == 1) {
                    s += arr[i];
                }else s+= (-1 * arr[i]);
            }
            // If the sum is divisible by M
            if(s % m == 0) {
                // Print the solution! 
                for(int i =0; i < n; i++) {
                    if(st[i] == 1) {
                        cout << "+ " << arr[i] << " ";
                    }else cout << "- " << arr[i] << " ";
                }
                cout << "\n";
            }

        }

        void getSolutions(int k) {
            // Every generated array has the length of "n"
            // If k is greater than n, it means we could have a solution
            if(k == n) {
                printSol();
            }else{
                // Generate
                for(int i=0;i<=1;i++) {
                    // k -  the index of the element
                    // i - either 1 or 0 - if the array contains this element
                    st[k] = i;
                    getSolutions(k+1); //  Search for other elements
                }
                cout << "\n";
            }
             
        }
};



int main () {

    Generate obj(4,5); // Input : 5, 6, 7
    obj.getSolutions(0);
    /*
    Output : 
    -5-6-7
    +5-6+7
    -5+6-7
    +5+6+7
    */
    cout << "\n";
    

    Generate obj2(3,3); // Input : 3, 5, 6, 8
    obj2.getSolutions(0);
    /*
    Output : 
    -3-5+6-8
    -3+5+6-8
    +3-5-6+8
    +3+5-6+8
    */
    return 0;
}









