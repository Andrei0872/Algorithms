
# Link to the task : http://www.codewars.com/kata/the-observed-pin/train/python

from itertools import product,combinations

def get_pins(observed):
  
  # Define the keypad
  keypad = [['8','0'], ['1','2','4'], ['1','2','3','5'], ['2','3','6'], ['1','4','5','7'], ['2','4','5','6','8'],                                     
         ['3','5','6','9'], ['4','7','8'], ['5','7','8','9','0'], ['6','8','9']]
  
  # If the length of the given string is 1, then we will simply return the item in the keypad
  # Else, we will return a list that will contain items resulted from the concatenation of every corresponding element in keypad list
  # We will use a recursive function for that 
  return keypad[int(observed[0])] if len(observed) == 1 else [x+y for x in keypad[int(observed[0])] for y in get_pins(observed[1:])]      

 
def get_pins2(observed):
    ADJACENTS = ('08', '124', '2135', '326', '4157', '52468', '6359', '748', '85790', '968')                                    
    return [''.join(p) for p in product(*(ADJACENTS[int(d)] for d in observed))] # product() - generate cartesian product


print get_pins("11")


print get_pins2("11")
