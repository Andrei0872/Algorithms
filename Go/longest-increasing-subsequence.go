package main

import (
	"fmt"
)

func detLIS(v []int) {
	valuesLen := len(v)
	lenSeq := make([]int, valuesLen)

	// an element represents a LIS of length 1
	for i := range v {
		lenSeq[i] = 1
	}

	maxLISLen := 1
	maxLisIdx := 0

	for i := 1; i < valuesLen; i++ {
		for j := 0; j < i; j++ {
			if v[i] > v[j] && lenSeq[i] <= lenSeq[j] {
				lenSeq[i] = lenSeq[j] + 1

				if lenSeq[i] > maxLISLen {
					maxLISLen = lenSeq[i]
					maxLisIdx = i
				}
			}
		}
	}

	seq := make([]int, 0)
	tailElem := v[maxLisIdx]

	maxLISLen++
	for maxLISLen > 0 && maxLisIdx >= 0 {
		crtLen := lenSeq[maxLisIdx]
		crtElem := v[maxLisIdx]

		if crtLen != maxLISLen-1 || crtElem > tailElem {
			maxLisIdx--
			continue
		}

		seq = append([]int{crtElem}, seq...)
		tailElem = crtElem
		maxLISLen--
		maxLisIdx--
	}

	fmt.Println(seq)
}

func main() {
	// [2 4 5 7 10]
	v := []int{9, 7, 3, 6, 2, 8, 5, 4, 5, 8, 7, 10, 4}
	detLIS(v)

	// [5]
	// detLIS([]int{5, 4, 3, 2, 1})
}
