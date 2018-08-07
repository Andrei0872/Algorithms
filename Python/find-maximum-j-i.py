
# Given a list, find the maximum j-i such that list[j] > list[i]

def solve(lst):

    # We need 2 other lists
    # leftMin[i] - will store the smallest element on the left side of arr[i],including arr[i]
    # rightmax[i] - will store the biggest element on the right side of arr[i],including arr[i]

    leftMin = [0 for i in range(len(lst))]
    # Start with the first element in order be able to fill the array properly
    leftMin[0] = lst[0]
    for i in range(1,len(lst)):
        leftMin[i] = min(leftMin[i-1],lst[i])


    rightMax = [0 for i in range(len(lst))]
    # We will start backwards, because we need the elements from the right side of a[j]
    rightMax[len(lst)-1] = lst[-1]
    for i in range (len(lst)-2,-1,-1):
        rightMax[i] = max(rightMax[i+1],lst[i])

    i,j,maxDif = 0,0,-1

    while i < len(lst) and j < len(lst):
        if(leftMin[i] < rightMax[j]):
            # Determine the maximum difference and store the positions
            if j-i > maxDif:
                maxDif = j-i
                start = i
                end = j
            j += 1 
        else:
            # Find a "greater" min value
            i +=1
    return {"maxDif":maxDif,"start":start,"end":end}

lst = [34, 8, 10, 3, 2, 80, 30, 33, 1]
res = solve(lst)
print(res) # {'start': 1, 'end': 7, 'maxDif': 6}

