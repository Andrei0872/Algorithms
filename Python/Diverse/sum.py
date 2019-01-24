'''
You're given the following formula:

S1=a1+a2+…+an
S2=a1⋅a2+a1⋅a3+…+an−1⋅an
S3=a1⋅a2⋅a3+a1⋅a2⋅a4+…+an−2⋅an−1⋅an
...
Sn=a1⋅a2⋅…⋅an.

Given an array of 'n' integers and a number 'k', determine 'Sk'
'''

def solve(arr, len, k):
    if k == 0:
        return 1
    if len == -1:
        return 0
    return arr[len] * solve(arr, len - 1, k - 1) + solve(arr, len - 1, k)

arr = [1, 2, 3]
k = 2

print(solve(arr, len(arr) - 1, k))