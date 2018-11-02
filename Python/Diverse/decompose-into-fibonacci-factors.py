
# Decompose a number into fibonacci factors

# Example : 80 = 55 + 21 + 3 + 1

'''
Reasoning :
    1) Have a function the returns the nth factor from fibonacci series
    2) Have a function that returns a number that is less or equal than the given number
    3) The function from step 2) will be called until the given number reaches 0 
'''

# Get the nth fibonacci factor
def getFib(n):
    fib = [1,1]
    for i in range(2,n): 
        fib.append(fib[i-1] + fib[i-2])
    return fib[n-1]

# Recursive alternative
def fibRec(n):
    return 1 if n <=2 else fibRec(n-1) + fibRec(n-2)


# Decompose that number
# x -  the given number
# n - the number that is less or equal than x
def decompose(x,n):
    # In order to find n, we need to stop when n gets a value that is NOT less or equal than x
    if(getFib(n+1) <=x):
        # We keep on increasing n
        decompose(x,n+1)
    else :
        # Now that we have n, get the nth fibonacci number
        fib_number = getFib(n)
        print fib_number
        
        # Search for other factors
        if (x - fib_number > 0) : decompose(x-fib_number,0) # We also reinitialize x

decompose(80,0) # 55 21 3 1 
decompose(121,0) # 89 21 8 3 

