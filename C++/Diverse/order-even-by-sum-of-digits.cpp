
/* 
Given an array of `n` elements, return the same array but with even numbers 
in descending order depending on the sum of their digits

Input:
size = 5
arr[] = {123, 2244, 5282, 4679, 548};

Output: 
123 5282 548 4679 2244
*/

#include <iostream>
using namespace std;

int sumOfDigits (int num) {
    int sum = 0;

    while (num) {
        sum += num % 10;
        num /= 10;
    }

    return sum;
}

int findBiggerSumOfDigits (int arr[], int indexes[], int size) {
    int maxSum = -32000;
    int indexMax = -1;

    for (int i = 0 ; i < size; i++) {
        if (indexes[i] == - 1) continue;

        int currentSum = sumOfDigits(arr[indexes[i]]);

        if (currentSum > maxSum) {
            maxSum = currentSum;
            indexMax = i;
        }
    }

    if (indexMax != -1) indexes[indexMax] = -1;
    return indexMax;
} 

void solve (int arr[], int size, int result[]) {
    int indexes[size], descOrder[size], storeIndexes[size];
    int len_indexes = 0;
    
    for (int i = 0; i < size; i++) indexes[i] = -1, storeIndexes[i] = -1;

    for (int i = 0; i < size; i++)
        arr[i] % 2 == 0 ? (indexes[i] = i, storeIndexes[i] = i, len_indexes++) : 0;

    int cnt = 0;
    while (cnt < len_indexes) {
        int maxIndex = findBiggerSumOfDigits(arr, indexes, size);
        descOrder[cnt++] = arr[maxIndex];
    }
    
    for (int i = 0, descOrderIndex = 0; i < size; i++) {
        result[i] = storeIndexes[i] == -1 ? arr[i] : descOrder[descOrderIndex++];
    }
}

int main () {
    int result[101];
    int arr[] = {123, 2244, 5282, 4679, 548};
    int size = 5;   

    solve(arr, size, result);

    for (int i = 0; i < size; i++) {
        cout << result[i] << " ";
    }

    return 0;
}