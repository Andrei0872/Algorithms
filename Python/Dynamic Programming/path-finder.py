
# https://www.codewars.com/kata/path-finder-number-3-the-alpinist/train/python

#* Path Finder (The alpinist)

from collections import deque

def path_finder(area):
    mountain = list(map(lambda item: [int(val) for val in item], area.split('\n')))
    size = len(mountain)
    # dist, row, col
    queue =  deque()
    queue.append([0,0,0])
    result = dict.fromkeys([str(i) + ":" + str(j) for j in range(size) for i in range(size)], 32000)
    result["0:0"] = 0

    while queue:
        [dist , row, col]= queue.popleft()

        for coords in [[-1,0],[1,0],[0,-1],[0,1]]:
            new_row = coords[0] + row 
            new_col = coords[1] + col

            if new_row < 0 or new_row >= size or new_col < 0 or new_col >= size:
                continue
            
            cost = abs(mountain[row][col] - mountain[new_row][new_col])
            total_dist = cost + dist
            if total_dist >= result[str(new_row) + ":" + str(new_col)]: 
                continue 
            
            result[str(new_row) + ":" + str(new_col)] = int(total_dist)
            queue.append([total_dist, new_row, new_col])

    
    return result[str(size -1 ) + ":" + str(size -1)]





b = "\n".join([
  "010",
  "010",
  "010"
])


print(path_finder(b)) # 2
