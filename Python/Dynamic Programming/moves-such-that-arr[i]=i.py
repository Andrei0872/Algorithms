'''
You're given an array of `n` numbers.
Determine the moves needed in order to make arr[i] = i

Note: You can use the `n + 1` space in order to make the moves

Example:
5
2 5 4 3 1 

7
1 6
5 1
2 5
6 2
3 6
4 3
6 4

Explanation

25431_
_54312
1543_2
1_4352
12435_
12_354
123_54
12345_
'''

NMAX = 105
empty = None

def make_move(src):
    global empty

    # Register move
    moves.append([src, empty])
    # Move the src to dest
    space[empty] = space[src]
    # Update after the move has been made(keep track of the position)
    where[space[src]] = empty
    space[src] = -1
    empty = src

def solve(n):
    global empty

    for i in range(n):
        num = int(input())
        # The initial state
        space[i] = num - 1
        # where[space[i]] = i : the elem space[i] should be at the `i` index  
        where[space[i]] = i

    empty = n 

    for i in range(n):
        if space[i] != i:
            # If this elem is not empty
            if space[i] != -1:
                make_move(i)
            make_move(where[i])

    print(len(moves))
    for src, dest in moves:
        print(src + 1, dest + 1)
    

n = int(input())

space = [-1] * NMAX
where = [-1] * NMAX
moves = []

solve(n)

