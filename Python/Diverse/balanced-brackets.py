
# Balanced Brackets 

def balanced(expression):
    queue = []
    opened = "{[("
    closed = "}])"
    mapping = dict(zip(opened, closed))
    

    def solve():
        for letter in expression:
            if letter in opened:
                queue.append(mapping[letter])
            elif letter in closed:
                if not queue or letter != queue.pop():
                    return False
        return not queue

    return solve                


expr = "{[(([{}]))]}{([])}"
print("OK") if balanced(expr)() else print("NOT OK") # OK

expr = "{[(([{}]))]}{([])}(()"
print("OK") if balanced(expr)() else print("NOT OK") # NOT OK


expr = "{[(([{[}]}]))]}{([])}"
print("OK") if balanced(expr)() else print("NOT OK") # OK

expr = "{[(([{}]))]}{([])}"
print("OK") if balanced(expr)() else print("NOT OK") # NOT OK