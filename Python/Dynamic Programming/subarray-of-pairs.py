'''
You're an array of 'n' pairs(p1, p2), and 2 numbers, 'p' and 'q'
Determine the subarray of pairs such that the sum of p1s = p and p2s = q

Example
5 6(p) 4(q)
4 2
1 2
4 1 
2 1 
3 1

Output:
3 1 
2 1
1 2

q p
6 4
'''

from collections import defaultdict
import re

def compute_key(num1, num2):
    return '{0}:{1}'.format(num1, num2)

def solve (arr, p, q):
    # memo[p1i][p2j] = index_arr
    memo = defaultdict(int)
    memo["0:0"] = 0

    for index in range(len(arr)):
        p1_index, p2_index = arr[index]
        for memo_index in list(memo):
            row, col = map(int, re.match('(\d+):(\d+)', memo_index).groups())
            new_row, new_col = row + p1_index, col + p2_index
            key = compute_key(new_row, new_col)

            if new_row > p or new_col > q:
                continue
            
            memo[key] = index

    row, col = p, q
    while memo[compute_key(row, col)] is not 0:
        arr_index = memo[compute_key(row, col)]
        print(arr[arr_index][0], arr[arr_index][1])
        row -= arr[arr_index][0]
        col -= arr[arr_index][1]


arr = [[4,2], [1,2], [4,1], [2, 1], [3, 1]]
p = 6
q = 4

print(solve(arr, p,  q))