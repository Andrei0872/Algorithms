

# Find the number of negative integers in a row-wise / column-wise sorted matrix

# Row-wise
row_wise = [[-4,-2,-1,8],
            [-1,0,6,7],
            [1,2,3,4]]
# Expected output : 4 

# Column-wise
column_wise = [[-3,-4,5,1],
               [-2,-1,7,2],
               [-1,0,9,6],
               [1,2,10,7]]
# Expected output : 5

'''
Reasoning : 
    1) We will start from the top right corner
    2) Look for the last negative integer
    3) When found, add to the count variable the index number + 1 -  because again, it is the last number on the row 
    4) Move to the next row and do the same thing
'''

# n,m -  the dimensions of that matrix
# mat -  the matrix
def negativeIntegers(mat,n,m):
    # We will loop through the rows as we would normally do
    i = 0
    
    # We start from top right corner
    j = m - 1
    
    # Number of negative integers     
    count = 0
    while j >= 0 and     i < n:
        if(mat[i][j] < 0):
            # We found a negative interger
            count += (j + 1) # Current index  + 1 
            # Go to the next row
            i += 1
        else:
            # Keep looking for a negative interger on the same line!
            j -= 1    

    return count


print negativeIntegers(row_wise,len(row_wise),len(row_wise[0])) # 4

print negativeIntegers(column_wise,len(column_wise),len(column_wise[0])) # 5

