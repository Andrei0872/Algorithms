
// // Find common letters of 2 strings

// #include <iostream>
// #include <cstring>
// using namespace std;

// void commonLetters(char s1[], char s2[]) {

//     // Use 2 vector to count the occurrences
//     int *fr1 = new int[26];
//     int *fr2 = new int[26];

//     // First string
//     for(int i  = 0; i < strlen(s1);i++) {
//         // ~undefined = -1
//         // ~1 = -2; -~1 = 2 and so on..
//         fr1[s1[i] - 97] = -~fr1[s1[i] - 97];
//     }

//     // Second string
//     for(int i  = 0; i < strlen(s2);i++) {
//         fr2[s2[i] - 97] = -~fr2[s2[i] - 97];
//     }

//     for(int i =0; i <= 25;i++) {
//         // If there is a common letter
//         if(fr1[i] && fr2[i]) {
//             cout << char(i + 97) <<" ";
//         }
//     }
// }

// int main (){
    
//     char s1 [] = "asdajdasm" ;
//     char s2 [] = "dasmkmkqsk";
//     commonLetters(s1,s2); // a d m s
//     return 0;
// }   


// Sparse search

//? Reference : https://www.geeksforgeeks.org/sparse-search/

/*
Example : 
    arr [] = {"for", "geeks", "", "", "", "", "ide", 
                      "practice", "", "", "", "quiz"}
    Output : geeks
*/


// #include <iostream>
// #include <cstring>
// using namespace std;

// int binarySearch(char arr[][100], int low, int high, char word[]) {
//     // Base case - element does not exist
//     if(low > high )
//         return -1;
    
//     // Get the middle
//     int mid = (low+high)/2;

//     // If it is an empty string, we modify a little bit
//     if(strcmp(arr[mid],"") == 0) {
//         // Take the immediately left and right positions
//         int left = mid -1 ;
//         int right = mid +1;
        
//         while (1) {

//             // If we don't find any non-empty strings
//             if(left < low || right > high) {
//                 return -1;
//             }
//             if(left >= low && strcmp(arr[left],"") != 0 ){
//                 // We find the actual mid position
//                 mid = left;
//                 break;
//             }
//             if(right <= high && strcmp(arr[right],"") != 0) {
//                 mid = right;
//                 break;
//             }
//             // Keep searching
//             left--;
//             right++;
//         } 
//     }

//     // Basic Binary Search
//     if(strcmp(arr[mid],word) == 0) {
//         // We found the element
//         return mid; 
//     }
//     if(strcmp(arr[mid],word) > 0) {
//         return binarySearch(arr,low,mid-1,word);
//     }else return binarySearch(arr,mid+1,high,word); 
// }

// int sparseSearch(char arr[][100],int low, int high, char word[]) {
//     // A little bit modified binary search
//     return binarySearch(arr,low,high,word);
// }

// int main () {

//     char arr[][100]= {"for", "geeks", "", "", "", "", "ide", 
//                       "practice", "", "", "", "quiz"};

//     char word[] = "geeks";
//     int len = sizeof(arr)/sizeof(arr[0]);

//     cout << sparseSearch(arr,0,len-1,word); // 1 
//     return 0;
// }




// UBB - Concurs Admitere - Aprilie -2016 - Subiectul 3

// #include <iostream>
// using namespace std;

// // Citirea vectorului de la tastatura
// int * citire(int *arr, int &n) {
    
//     cin  >> n;
    
//     arr = new int[n];
    
//     for(int i=0; i < n; i++){
//         cin >> arr[i];
//     }
//     return arr;
// }

// // Verificarea daca un sir este palindrom sau nu
// bool palindrom(int arr[], int n) {
 
//     for(int i=0; i < n/2;i++) {
//         if(arr[i] != arr[n-i-1])
//             return false;
//     }
        
//     return true;
// }

// void nrPermutari(int *arr, int n, int &nrPerm,bool &gasit) {

//     // Inca nu am gasit nimic
//     gasit = false; 
//     int temp;
//     // Putem verifica daca sirul dat este din prima palindrom
//     if(palindrom(arr,n)) {
//         gasit = true;
//         return;
//     }else {
//         // Cat timp nu s a gasit si cat timp nu s-a repetat permutarea
//         // Folosim asta pt a evita un loop infinit
//         while(!gasit && nrPerm <= n) {

//             // Facem permutarile
        
//             // Retinem primul element
//             temp = arr[0];
//             // Schimbam locurile elementelor
//             for(int j=1; j<n;j++)
//                 arr[j-1] = arr[j];
//             // Primul element devine ultimul
//             arr[n-1] = temp;

//             // Vedem daca vectorul rezultat din permutare este palindrom
//             gasit = palindrom(arr,n);

//             // Marim numarul de permutari ciclice
//             nrPerm++; 
//         }
//     }
// }

// void palindromCiclic(int *arr, int n) {
//     // Vedem daca vectorul sau una din permutarile sale este palindrom si, in caz afirmativ, vom avea si numarul de permutari
//     int nrPerm = 0;
//     bool gasit;
//     nrPermutari(arr, n,nrPerm,gasit);
    
//     // Daca s-a gasit vreo permutare, afisam mesajul corespunzator si nr de permutari necesare
//     if(gasit) {
//         cout << "Da\n";
//         cout << "Numarul de permutari necesare : " << nrPerm << "\n";
//     }else {
//         cout << "Nu\n";
//     }
// }


// int main () {

//     int *arr;
//     // Lungimea vectorlui
//     int n;

//     arr = citire(arr,n);
//     palindromCiclic(arr,n);

//     // Eliberam memoria
//     delete[] arr;
//     return 0;
// }


// // Se da un numar natural. Extrageti numarul format din cifre impare, in ordinea aparitiilor incepand de la stanga

// #include <iostream>
// #include <cmath>
// using namespace std;

// // Pentru a determina puterea lui 10
// int c =0;
// int rec(int n) {
 
//     if(n > 0) {
//         return (n%10) & 1 ? n%10*pow(10,c++) + rec(n/10):rec(n/10);
//     }else{
//         c = 0;
//         return 0; 
//     } 

// }


// int main() {
//     int n = 2103;
//     cout << rec(n) << "\n";
//     cout << rec(2513) << "\n";
//     return 0;
// }



// // pow() alternative
// #include <iostream>
// using namespace std;

// int power(int st, int dr, int a) {

//     if(st == dr) {
//         return a;
//     }
//     else return power(st,(st+dr)/2,a) *  power((st+dr)/2+1,dr,a);
// }

// int power2(int a, int b) {
//     if(b == 0 ) return 1;
//     if(b & 1) return a * power2(a,b/2) * power2(a,b/2);
//     else return power2(a,b/2) * power2(a,b/2);
// }

// int main () {
//     // 2 ^ 3
//     cout << power(1,3,2) << "\n"; // 8
//     // 5 ^ 3
//     cout << power(1,3,5) << "\n"; // 125


//     cout << power2(2,3) << "\n"; // 8
//     cout << power2(5,4) << "\n"; // 625

// }



// #include <iostream>
// #include <string>
// #include <cstring>
// using namespace std;

// int main () {
//     string s  ="andrei";
//     cout << s.c_str(); // Returns a pointer to an array that contains a null terminated sequence if ch(C string)
//     char *str = new char[s.length() + 1];
//     strcpy(str,s.c_str()); // andrei
//     cout << "\n" << str;


//     cout << "\n";
    
//     string s2 = "ANDREI";
//     char str2[255];
//     strcpy(str2,s2.data()); // Returns a pointer to the c-string representation of the string object's value
//     cout << str2 << "\n"; // ANDREI

// }



// // C++ priority_queue
// #include <iostream>
// #include <queue>
// #include <vector>
// using namespace std;

// int main() {

//     // Min
//     priority_queue<int,vector<int>,greater<int>> q;
//     q.push(30);
//     q.push(10);
//     q.push(40);
//     q.push(50);
//     q.push(33);

//     cout << q.size() << "\n";

//     while(!q.empty()) {
//         cout << q.top() << " "; // 10 30 33 40 50
//         q.pop();
//     }

//     cout << "\n";

//     priority_queue<int> q2;
//     q2.push(30);
//     q2.push(10);
//     q2.push(40);
//     q2.push(50);
//     q2.push(33);

//     while(!q2.empty()) {
//         cout << q2.top() << " "; // 50 40 33 30 10
//         q2.pop();
//     }
//     return 0;
// }

// // Implementing Min Heap on a defined class
// #include <bits/stdc++.h>
// using namespace std;

// class Point {

//     // Private variables
//     int x,y;
//     public:
//         // Construct
//         Point(int _x, int _y) {
//             x = _x;
//             y = _y;
//         }

//     int getX() const {return x;}
//     int getY() const {return y;}

// };

// // Compare 2 points
// class myComparator{
//     public:
//         int operator() (const Point &p1, const Point &p2) {
//             // Min 
//             return p1.getX() > p2.getX();
//         }
// };

// int main () {

//     priority_queue<Point,vector<Point>, myComparator> q;

//     // We add new instances in the heap
//     q.push(Point(10,2));
//     q.push(Point(2,1));
//     q.push(Point(1,5));

//     // Print the heap
//     while(!q.empty()) {
//         // Create a new instance first
//         Point p = q.top();
//         cout << p.getX() << " " << p.getY() << "\n";
//         q.pop();
//     }
//     /*
//     Output : 
//     1 5
//     2 1
//     10 2
//     */
//     return 0;
// }

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









