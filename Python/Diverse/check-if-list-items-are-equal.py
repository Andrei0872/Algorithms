

#* Check if all elements in list are equal

# Given list 
lst = ['a','a','a']  

# print(set(lst))  # ['a']


# First alternative
if len(set(lst)) == 1 : # set() - create a set - unindexed and unordered elements
    print("all equal x1")

# Second alternative
if lst.count(lst[0]) == len(lst): # if the number of occurences is equal to the length of the list
    print("all equal x2")


# Third alternative    
# all() returns true if all elements in the iterable obj are true
if all(x == lst[0] for x in lst):
    print("all equal x3")
