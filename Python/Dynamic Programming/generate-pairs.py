'''
You're given a number of people `N`, a number of days `D`, and a maximum number of pairs `P`.
Your task is to generate an array of N elements such that the days are grouped in pairs.
The days' number can go up to `D`;

Example: 
5 465 4

Output:
1 1 1 2 2 # 2-2, 1-1, 1-1, 1-1

Some remarks

2nums ... 1pair
3nums ... 3pairs
4nums ... 6pairs
5nums ... 10pairs
6nums ... 15pairs
...
'''


def solve(N, D, P):
    # We would generate an array "nrCnt" where nrCnt[i] = x - x pairs for i numbers

    nrCnt = []
    nrCnt.append(0)
    nrCnt.append(0)
    nrCnt.append(1)

    # We only need to generate N pairs (relying on the remark above)
    nums = 2
    temp = 2
    while True:
        nums +=1
        nrPairs = nrCnt[nums - 1] + temp

        if nrPairs > P:
            break

        nrCnt.append(nrPairs)
        temp +=1

    result = []
    index_day = 1
    index_number_pairs = len(nrCnt) - 1

    while index_day <= D and len(result) < N:
        if P >= nrCnt[index_number_pairs] and nrCnt[index_number_pairs] != 0:
            P -= nrCnt[index_number_pairs]
            day_number = index_day
            day_cnt = 1

            while day_cnt <= index_number_pairs and len(result) < N:
                result.append(day_number)
                day_cnt += 1

            index_day += 1
        elif P < nrCnt[index_number_pairs]:
            index_number_pairs -= 1
        else:
            result.append(index_day)
            index_day += 1
    
    print(result)


print(solve(5, 365, 4)) # [1, 1, 1, 2, 2]
print(solve(17, 100, 12)) # [1, 1, 1, 1, 1, 2, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11]