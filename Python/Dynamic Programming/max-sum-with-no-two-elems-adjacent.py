'''
Given an array, determine the maximum sum such that no two elements are adjacent

Example
arr = [3, 7, 5, -1, 6, 6, 2]

Output: 16 (3 + 5 + 6 + 2)
'''

def solve (arr):
    # The key is to maintain 2 sums, 
    # one in which we include the prev element,
    # one in which we exclude the prev element

    include_prev, exclude_prev = 0, 0

    for elem in arr:
        # Current max sum excluding `elem`
        exclude_this_elem = include_prev if include_prev > exclude_prev else exclude_prev

        # Current max sum including `elem`
        include_prev = exclude_prev + elem

        # Computing the sum excluding this elem
        exclude_prev = exclude_this_elem

    return include_prev if include_prev > exclude_prev else exclude_prev



arr = [3, 7, 5, -1, 6, 6, 2]

print(solve(arr))