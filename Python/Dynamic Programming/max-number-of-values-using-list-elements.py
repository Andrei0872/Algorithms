'''
Given an array of "n" numbers, determine the maximum number of values
that can be obtained using the elements in the given array

Example
n = 2
arr = [6, 3]

Output:
3

Explanation
The maximum number of values is given by: 3, 6 and 9(combining 3 and 6)
'''

def solve (arr):
    solutions = [None] * NMAX
    solutions[0] = 0
    last_piece = [-1] * NMAX
    max_reached = 0

    # solutions[j + val] is None - we haven't used this "combination" yet
    # last_piece[j + val] < index - avoid using the same element more times
    # solutions[j] == j - checks if we have used this element

    for index, val in enumerate(arr):
        for j in range(max_reached, -1, -1):
            if solutions[j + val] is None and last_piece[j + val] < index and solutions[j] == j:
                solutions[j + val] = j + val
                last_piece[j + val] = index
                max_reached = max(max_reached, j + val)

    return len(list(filter(None, solutions)))


NMAX = 500
arr = [6, 3]

print(solve(arr)) # 2 

print(solve([6, 3, 2])) # 7 :[0, None, 2, 3, None, 5, 6, None, 8, 9, None, 11, None, None, None]

print(solve([6, 3, 2, 1])) # 12 