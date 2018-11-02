
# User input : a matrix of mxm; an array of n elements
# Items of the array and matrix must be integers with maximum 5 digits
# Determine how many times the item with most occurrences in the array can be found in the matrix; When found, print its position in matrix


# Example :
#     matrix : [[1, 2, 4], [5, 9, 4], [1, 2, 3]]
#     array: [4, 10, 7, 4, 2, 6]
    
#     Result : line :  1 ; column :  3
#              line :  2 ; column :  3


# Create matrix -  2 alternatives 
# * First Alternative
def create_mat():
    print "Matrix dimension : "
    m = int(raw_input())
    mat = [0] * m # [0,0,0... m times]

   # Create an empty matrix
    for i in range(m):
        mat[i] = [0] * m
    
    # Fill the matrix
    for i in range(m):
        for j in range(len(mat[i])):
             mat[i][j] =  int (raw_input())


    return mat


#* Second Alternative
def create_mat_v2():
    # Matrix dimensions
    m = int(raw_input())

    # Create an empty matrix
    mat = [ [] for i in range(m)]

    # Fill the matrix with elements from user input
    for i in range(len(mat)):
        mat[i] = [ int(raw_input()) for j in range(m) ] # Here could be range(n) if we had a matrix of mxn

    return mat


# Create array
def create_array():
    # Length of the array
    n = int(raw_input())
    return [ int(raw_input()) for i in range(n) ]


# Find the element with the most occurrences
def search_item(arr):
    # Maximum number of occurrences
    maxim = -1 
    
    for i in arr:
        occ = arr.count(i)
        if(occ > maxim):
            maxim = occ
            item = i

    return item


# Search for that item in the matrix
def search_in_matrix(mat,elem):
    #  Occurrences
    occurrences = 0
    for i in range(len(mat)):
        for j in range(len(mat[i])):
            # If the element is found
            if(mat[i][j] == elem ):
                occurrences +=1
                print "line : ",i+1,"; column : ",j+1



mat1 = create_mat()
print "mat1 : ", mat1
# mat2 = create_mat_v2()
# print "mat2 : ", mat2


arr = create_array()
print "array :",arr

# Item with the most occurrrences in the array
elem =  search_item(arr)

search_in_matrix(mat1,elem);

