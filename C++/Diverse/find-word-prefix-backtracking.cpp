/*
 
 
 Given a matrix (nXm) of characters,determine the longest prefix for a given word
 The letters that are part of the word MUST BE on the same column, or on the same row.
 
 
 
 Reasoning : {
 	-first loop through the characters(letters) 
 	-when i discover a letters which is identical to the first letter of the given word {
 		I start a  backtracking algorithm {
 			-I get the letter's neighbors (remember that any neighbor must be on the same line/column with the current letter)
 			- verify if the concatenation of the actual letter and its neighbor is found in the given word
 			-if so, i keep on searching for neighbors
 			-unless,I determine the maximum length of the prefix I found so far and save the letters' coordinates within a "deque" (this will come handy when i must print the letters that compose the prefix )
			}
 	}
 }
 
 Example : {
 	for the given m and n : m=4, n=4,
		the given matrix : e f s p
				   c c a u
				   o b c t
				   v n a s
		the given word : "castelan"
		
	the suitable output is : cast and the letters' position : (3,3), (4,3),(4,4),(3,4)
 }
 
*/

#include <iostream>
#include <cstring>
#include <deque>
using namespace std;

int n,m; //the dimension of the matrix

//we use this for directions
const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};


deque<pair<int,int>> q; //the one we'll work with
deque<pair<int,int>> q_corect; //the one in which we'll store the final result

int maxim = -32000; 

 char a[100][100]; 

char s[255]; //the given string

//readData() = getting the input
void readData() {

	cout << "n= "; cin>>n;
	cout << "m= "; cin>>m;
	cin>> s;
	
	char c;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			cin  >> c;
			a[i][j] = c;
		}
	} 
}


//check if the concatenation of any 2 letters are part of the given word
int valid(int y, int x, int y_actual, int x_actual) {
	//if one of them is OUTSIDE the matrix
	if(y<1 || y > n || x<1 || x>m)
		return 0;
	//getting the concatenation
	int k=0;
	char str [255] = "";
	str[k++] = a[y_actual][x_actual];
	str[k++] = a[y][x];
	str[k] = 0;
			
	if(!strstr(s,str))
		return 0;
	
	//if all went well...
	return 1;	
	
}


void back(int k,int y, int x) {
// 	looping through the directions array
	for(int i=0;i<4;i++) {
		//getting the neighbors
		int xx = x+dx[i]; 
		int yy = y+dy[i];
		//checking if the concatenation fulfills the condition
		if(valid(yy,xx,y,x)) {
			//adding to deque
			q.push_back(make_pair(yy,xx));
			//keep on searching 
			back(k+1,yy,xx);
			//we want to get all possible cases
			q.pop_back();
		}else { //if not match is found
			//we determine the maximum
		int lung = q.size();
		if(lung > maxim ) {
			maxim = lung;
			//store the corret deque
			q_corect = q;
		}
	}

}
}

void rez()  {
	for(int y=1;y<=n;y++) {
		for(int x=1;x<=m;x++) {
			if(strchr(s,a[y][x]) &&  a[y][x]==s[0]) {
				//we first clear what we had
				q.clear(); 
				q.push_back(make_pair(y,x));
				back(1,y,x);
			}
		}
	}
}

void printResult() {
	//printing the result
while(!q_corect.empty()) {
	cout << a[q_corect.front().first][q_corect.front().second] << " ";
	q_corect.pop_front(); //delete in order to get the next set of coordinates
}
}

int main () {

	readData();	
	rez();
	printResult();

return 0;	
}