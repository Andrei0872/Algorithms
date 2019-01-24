
'''

You're given an array of numbers. The array can be split in different ascending subarrays.
Determine the min number of subarrays.

Example:
8
4 6 2 5 8 1 3 7
Output:
3

Explanation:
4 6 8, 2 5 7, 1 3

Another way of splitting
4 5 7
6 8
2 3
1

'''

n = int(input())
memo = [0] * (n + 1)
memo[0] = 1e9
k = 0
# memo[i] - the end of i-th subarray

for i in range(n):
    num = int(input())
    
    # If we find a new "end" for a subarray
    if num < memo[k]:
        k = k + 1
        memo[k] = num
    else:
        # num will be the new last element for the subarray `index`
        index = 1
        # Stop where num is greater than the current last element for the subarray `index`
        while memo[index] > num:
            index += 1
        memo[index] = num 

print(k)