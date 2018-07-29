
#   Min Cost Path


'''
 Given a cost matrix and a positon, write a function that returns cost of minimum
 cost path to reach that position, starting from 0

 You can only travers down,right and diagonally
'''

'''
Exaple : 

 1 2 3 
 4 8 2
 1 5 3

Output : 
8 (0,0 -> 0,1 -> 1,2 ->2,2) = 1 + 2 + 2 + 3

'''

'''
Reasoning {
    1) Notice that, for the position given, the min cost neighbor is the minimum value between {
        a) cost[n-1][m-1] - diagonal
        b) cost[n-1][m] - up
        c) cost[n][m-1] - left
    }
    2) Instead of using a recursive function, that will slow our execution, we can use a temporary array
}
'''


# n,m - coordinates for the position to be reached
def mcp(cost,n,m):
    
    # Temporary matrix -  it is empty at the beginning
    temp = [[0 for j in range(len(cost[0]))] for i in range(len(cost))]

    # Set the first element in the temporary matrix, so we can fill the other empty items
    temp[0][0] = cost[0][0]

    # Fill the first column with the cost path from top left to bottom left
    for i in range(1,n):
        temp[i][0] = temp[i-1][0] + cost[i][0]

    # Fill the first row with the cost path from top left to top right
    for j in range(1,m):
        temp[0][j] = temp[0][j-1] + cost[0][j]

    '''
    Based on the given matrix, we would have something like this (if m=n=3)
    temp = 1 3 6
           5
           6 
    ''' 

    # Fill the other items in temp matrix
    for i in range(1,len(cost)):
        for j in range(1,len(cost[0])):
            # temp[i][j] will equal to the min between the 3 neighbors(temp[n-1][m-1] etc..) +  plus the actual value from cost matrix
            temp[i][j] = min(temp[i-1][j-1],temp[i-1][j],temp[i][j-1]) + cost[i][j]

    # Return the value temp matrix has at the specified position
    return temp[n-1][m-1]


cost = [[1, 2, 3],
        [4, 8, 2],
        [1, 5, 3]]

print mcp(cost,3,3) # 8


cost2 = [[3, 1, 3,6],
        [4, 10, 1,1],
        [3, 0, 4,10]]

print mcp(cost2,3,2) # 7

