package subset_sum

import "fmt"

func printPath(mat [][]bool, values []int, rowLen, colLen int) {
	if !mat[rowLen][colLen] {
		return
	}

	path := make([]int, 0)

	crtRow, crtCol := rowLen, colLen

	for crtRow != 0 {
		if mat[crtRow][crtCol] == mat[crtRow-1][crtCol] {
			crtRow--
			continue
		}

		path = append([]int{values[crtRow-1]}, path...)
		crtRow--
		crtSum := crtCol
		crtCol = crtSum - values[crtRow]
	}

	fmt.Println("the path is: ", path)
}

func isSubsetSum(values []int, sum int) bool {
	rowLen := len(values) + 1
	columnLen := sum + 1

	mem := make([][]bool, rowLen)

	for i := 0; i < rowLen; i++ {
		mem[i] = make([]bool, columnLen)
		mem[i][0] = true
	}

	for itemIdx := 1; itemIdx < rowLen; itemIdx++ {
		for crtSum := 1; crtSum < columnLen; crtSum++ {
			crtItem := values[itemIdx-1]
			var finalVal bool

			if crtItem > crtSum {
				// it means we can just exclude the current element and get our result based on what we had **before** it
				finalVal = mem[itemIdx-1][crtSum]
			} else {
				// mem[itemIdx-1][crtSum] = not using the current element
				// mem[itemIdx-1][crtSum - crtItem] = using the current element,
				// 	and checking whether we get a valid result for the remaining sum
				finalVal = mem[itemIdx-1][crtSum] || mem[itemIdx-1][crtSum-crtItem]
			}

			mem[itemIdx][crtSum] = finalVal
			// fmt.Println(finalVal, mem[itemIdx][crtItem], itemIdx, crtSum)
		}
	}

	if res := mem[rowLen-1][columnLen-1]; res {
		printPath(mem, values, rowLen-1, columnLen-1)
		return true
	}

	return false
}

func main() {
	// values := []int{1, 3, 1, 5}
	// sum := 5

	// values := []int{3, 34, 4, 12, 5, 2}
	// sum := 9

	values := []int{3, 34, 4, 12, 5, 2}
	sum := 18

	fmt.Println(isSubsetSum(values, sum))
}
