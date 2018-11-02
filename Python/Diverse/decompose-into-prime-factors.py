
# Decompose a number into prime factors

def desc(n):
    d = 2
    while n > 1:

        p = 0 
        while not n % d:
            p = p + 1
            n = n / d

        if p != 0:
            print d,"^",p
        d = d +1
    


desc(315)
# Output : 
# 3 ^ 2
# 5 ^ 1
# 7 ^ 1