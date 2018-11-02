
# Smallest subarray with sum greater than a given value

def minSubArr(lst,x):
    # minLength = the subarray might also be the entire array, which means it is not possible to get a subarray
    s,minLength,n = 0,len(lst)+1,len(lst)


    start,end = 0,0

    while end < n:

        # Add elements until the sum reaches a value greater than x
        while s <= x and end < n: # (end < n) - we need to verify the condition here as well
            print('start : {0}, end : {1}, sum :{2} '.format(start,end,s))
            # If the sum is less than or eqal to 0, it means we might have encountered negative numbers
            # We must skip any subbarray that contains negative numbers
            # Because later on, we might need to remove starting elements in order to get the smallest subarray
            if s <= 0 and x > 0:
                start = end
                s = 0 # Reinitialize the sum

            s += lst[end]
            end = end + 1
        print('AFTER FIRST WHILE : start : {0}, end : {1}, sum :{2} '.format(start,end,s))
        # Remove starting elements if needed
        while s > x and start < n:
            minLength = min(minLength,end-start)
            print('min length : {0}, start : {1}, end : {2}, current sum : {3}'.format(minLength,start,end,s))
            s -= lst[start]
            start = start + 1 
    print('start : {0}, end : {1}, sum :{2} '.format(start,end,s))
    return minLength


lst = [1,4,45,6,0,19]
x = 51 
print(minSubArr(lst,x)) # 3

lst2 = [- 8, 1, 4, 2, -6]
x = 6
print(minSubArr(lst2,x)) # 3
