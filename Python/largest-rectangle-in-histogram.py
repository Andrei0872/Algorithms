

# Largest rectangle in histogram

# Task : Given a list of heights, determine the largest rectangle in histogram 

'''
Reasoning
    1) We will store the list indexes in a stack
    2) We will keep adding to the stack until the element with the top index 
        from the stack is grater than the element 
        whose index is about to be added to the stack
    3) When this happens, we must determine the maximum area found until then
    4) After we loop through the list, we apply the same reasoning until the stack is empty        
'''

# lst = Here you could have some user input or something like that
def largestRectangle(lst):

    # area - temporary area that will help us determine the maximum area - maxArea
    stack,maxArea,area,index = ([],0,0,0)
  
    listLength = len(lst)
    
    # Loop through the list 
    while index < listLength :

        # If the stack is empty or the condition is fulfilled : add index to the stack
        if not stack or lst[stack[len(stack)-1]] <= lst[index]:
            stack.append(index)
            index += 1 
        # Now we must determine the maximum area of that rectangle
        else:
            # Get the value which has its index on top of the stack
            top_stack = lst[stack[len(stack)-1]]

            # Get rid of the top index because we don't need it anymore to find the correct rectangle area 
            stack.pop()

            # Get the temporary area
            area = top_stack * (index if not stack else (index - stack[len(stack)-1] - 1))

            # Find the maximum area 
            maxArea = max(maxArea,area)


    # Now we apply the same reasoning until the stack is empty
    while stack:
        top_stack = lst[stack[len(stack)-1]]
        stack.pop()
        area = top_stack * (index if not stack else ( index - stack[len(stack)-1] - 1))
        maxArea = max(maxArea,area)
    
    return maxArea



print largestRectangle([6, 2, 5, 4, 5, 1, 6]) # 12

print largestRectangle([4,2,3,5]) # 8
