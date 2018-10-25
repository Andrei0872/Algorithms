

'''
 In a given nXm matrix, each fields represents the amount of gold
 in tons. You can only move right, right-up and right-down
 Find out the maximum amount of gold he can collect
'''

'''
Example
Input: mat[][] = { {1, 3, 1, 5},
                   {2, 2, 4, 1},
                   {5, 0, 2, 3},
                   {0, 6, 1, 2}};
Output : 16
(2,0) -> (1,1) -> (1,2) -> (0,3) OR
(2,0) -> (3,1) -> (2,2) -> (2,3)
'''

def maxGold(matrix):
    row = len(matrix)
    col = len(matrix[0])
    prev_col = [0] * (row + 2)
    current_col = [-1] * (row + 2)
    successor = {}

    for j in range(col-1,-1,-1):
        for i in range(row-1,-1,-1):
            # Top right cell
            current_col[i+1] = prev_col[i]
            successor[(i,j)] = (i-1,j+1)
            # Right cell
            if current_col[i+1] < prev_col[i+1]:
                current_col[i+1] = prev_col[i+1]
                successor[(i,j)] = (i,j+1)
            # Bottom right cell   
            if current_col[i+1] < prev_col[i+2]:
                current_col[i+1] = prev_col[i+2]
                successor[(i,j)] = (i+1,j+1)                                    
                                   
            current_col[i+1] += matrix[i][j]
        prev_col = current_col[:]

    max_gold = max(current_col)
    start_pos = current_col.index(max_gold) - 1

    for i in range(row-1,-1,-1):
        successor[(i,col-1)] = None
    
    path = []
    succ = (start_pos,0)
    while succ != None:
        path.append(succ)
        succ = successor[succ]

    return max_gold, path

mat = [[1, 3, 3],
       [2, 1, 4],
       [0, 6, 4]];

max_val, path = maxGold(mat)

print("max value :", max_val)

print("The path is :")
for pos in path:
    print(pos)

