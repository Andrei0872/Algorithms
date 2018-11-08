
'''
Given a sum of money, find the minimum number of coins needed to equal the given sum 
'''

def min_coin(money, amount):
    result = []
    while amount != 0:
        for i in range(len(money)):
            if money[i] > amount:
                amount -= money[i-1]
                result.append(money[i-1])
                break
    return result, len(result)


money = [1, 2, 5, 10, 20, 50, 100, 500, 1000]
print("Enter the value:")
n = int(input())
print(min_coin(money,n))