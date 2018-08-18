

// Longest subarray with sum k


/**
 * Example {
 *  1) 
 *   arr = {10, 5, 2, 7, 1, 9 }
 * 	 k = 15 
 * 	 Output : 4 ({5, 2, 7, 1}) 
 * 
 *  2) 
 * 	arr = {-5, 8, -14, 2, 4, 12}
 *  k = -5
*  Output : 5 ({-5, 8, -14, 2, 4})
 * }
 * 
*/

#include <iostream>
#include <unordered_map>
using namespace std;

int getLength(const int arr[],int len,int k) {

	int sum = 0,
		maxLength,
		start,
		end;

	// Keep track of the sum at each index
	unordered_map<int,int> m;

	for(int i =0 ; i < len ;i++) {

		sum +=arr[i];

		// If the current sum has not been added
		if(m.find(sum) == m.end()) {
			m.insert(make_pair(sum,i));
		}

		// Get the current max length
        // This means the subarray starts from the very beginning
		if(sum == k ) {
			start = 0;
			end = i;
			maxLength = i+1;
		}

		// Get the max length
		// Check if we can "expand" our length 
		// This will help us to get all the possible cases
		if(m.find(sum-k) != m.end()) {
			if(maxLength < (i - m[sum-k])) {
				start = m[sum-k] + 1;
				end = i;
				maxLength = (i  - m[sum-k]);
			}
		}

	}


	cout << "start : " << start << "\n";
	cout << "end : " << end << "\n";
	return maxLength;

}

int main () {

	const int arr[] = {10, 5, 2, 7, 1, 9};
	const int k = 15;
	const int len = sizeof(arr)/sizeof(arr[0]);

	//cout << getLength(arr,len,k) << "\n"; // 4; start = 1; end = 4 


	const int arr2[] = {-5, 8, -14, 2, 4, 12};
	const int k2 = -5;
	const int len2 = sizeof(arr)/sizeof(arr[0]);

	cout << getLength(arr2,len2,k2) << "\n"; // 5; start = 0; end = 4

}

