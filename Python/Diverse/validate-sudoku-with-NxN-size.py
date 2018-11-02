

# Validate Sudoku with size NxN

# Link to the task : https://www.codewars.com/kata/validate-sudoku-with-size-nxn/train/python

from math import sqrt
class Sudoku(object):
     
    def __init__(self,data):
        self.data = data

    def is_valid(self):
        N = len(self.data)
        M = len(self.data[0])
        S = N * (N+1)//2;
        # If it is not NxN
        if(N != M ): return False
        # If it is not squared
        if(N % 1 != 0): return False
        if(N==1 and self.data[0][0] == '' or self.data[0][0] <=0   or self.data[0][0] > N): return False;
        
        
        # Sum on row
        sumRow = [0 for i in range(N)]
        # Sum on column
        sumCol = [0 for i in range(N)]
        # Sum in box - sqrt(N) x sqrt(N)
        sumBox = [[0 for j in range(int(sqrt(N)))] for i in range(int(sqrt(N)))]
        
        # Loop through the matrix
        for i in range(N):
            for j in range(N):
                if(str(self.data[i][j]).isalpha()): return False
                if self.data[i][j] <=0 or self.data[i][j] > N: return False
                #if ord(str(self.data[i][j])) > 57 and ord(str(self.data[i][j])) < 48 : return False
                # Get the sum on the row
                sumRow[i] += self.data[i][j]
                # Get the sum on the column
                sumCol[j] += self.data[i][j]
                # Get the sum in the box
                sumBox[i//int(sqrt(N))][j//int(sqrt(N))] += self.data[i][j]
        # I guess that's how you deal with "all()" when there is a multi-dimensional array
        if  all(all(sumBox[i][j] ==S for j in range(int(sqrt(N)))) for i in range(int(sqrt(N)))) == False: return False
        return all(lambda x:x == S for x in sumCol) and all(lambda y:y == S for y in sumRow)

goodSudoku1 = Sudoku([
  [7,8,4, 1,5,9, 3,2,6],
  [5,3,9, 6,7,2, 8,4,1],
  [6,1,2, 4,3,8, 7,5,9],

  [9,2,8, 7,1,5, 4,6,3],
  [3,5,7, 8,4,6, 1,9,2],
  [4,6,1, 9,2,3, 5,8,7],
  
  [8,7,6, 3,9,4, 2,1,5],
  [2,4,3, 5,6,1, 9,7,8],
  [1,9,5, 2,8,7, 6,3,4]
])

print goodSudoku1.is_valid() # True