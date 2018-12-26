

# Order tree by levels

'''
                 2
            8        9
          1  3     4   5

Output: [2,8,9,1,3,4,5]
'''

'''
                 1
            8        4
              3        5
                         7

Output: [1,8,4,3,5,7]
'''

class Node:
    def __init__(self, L, R, val):
        self.left =  L
        self.right = R
        self.value = val


def tree_by_levels(node):
    res, q = [],[node]

    while q:
        current_node = q.pop(0)
        if not current_node is None:
            res.append(current_node.value)
            q += [current_node.left, current_node.right]
    
    return res if node is not None else []



example1 = Node(Node(Node(None, None, 1),Node(None, None, 3),8),Node(Node(None, None, 4),Node(None, None, 5),9),2)
print(tree_by_levels(example1)) # [2, 8, 9, 1, 3, 4, 5]

example2 = Node(Node(None,Node(None, None, 3), 8),Node(None,Node(None,Node(None, None, 7),5),4),1)
print(tree_by_levels(example2)) # [1, 8, 4, 3, 5, 7]

