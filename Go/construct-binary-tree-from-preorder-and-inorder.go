package main

import "fmt"

// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

/*
Example 1
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]

Example 2
Input: preorder = [-1], inorder = [-1]
Output: [-1]
*/

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

const MAX_LEN = 3001

func indexOf(slice []int, elem int) int {
	for idx, val := range slice {
		if val == elem {
			return idx
		}
	}

	return -1
}

func buildTree(preorder []int, inorder []int) *TreeNode {
	var generateResult func(iStartIdx, iEndIdx, preIdx int) *TreeNode

	generateResult = func(iStartIdx, iEndIdx, preIdx int) *TreeNode {
		if preIdx > len(preorder)-1 || iStartIdx > iEndIdx {
			return nil
		}

		crtRoot := preorder[preIdx]
		inOrderRootIdx := indexOf(inorder, crtRoot)

		distExclusive := inOrderRootIdx - iStartIdx

		node := TreeNode{Val: crtRoot}

		node.Left = generateResult(iStartIdx, inOrderRootIdx-1, preIdx+1)
		node.Right = generateResult(inOrderRootIdx+1, iEndIdx, preIdx+distExclusive+1)

		return &node
	}

	return generateResult(0, len(inorder)-1, 0)
}

func main() {
	// res := buildTree([]int{3, 9, 20, 15, 7}, []int{9, 3, 15, 20, 7})
	// fmt.Println(res)

	// res := buildTree(
	// 	[]int{25, 15, 10, 4, 12, 22, 18, 24, 50, 35, 31, 44, 70, 66, 90},
	// 	[]int{4, 10, 12, 15, 18, 22, 24, 25, 31, 35, 44, 50, 66, 70, 90},
	// )
	// fmt.Println(res)

	// res := buildTree([]int{4, 3, 1, 2}, []int{1, 2, 3, 4})
	// fmt.Println(res)

	res := buildTree([]int{3, 2, 1, 4}, []int{1, 2, 3, 4})
	fmt.Println(res)

	// res := buildTree([]int{1, 2}, []int{1, 2})
	// fmt.Println(res)
}
