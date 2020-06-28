package main

import (
	"fmt"
	"math"
)

// https://www.codewars.com/kata/550498447451fbbd7600041c/

func Comp(array1 []int, array2 []int) bool {
	if array1 == nil || array2 == nil {
		return false
	}

	if len(array1) == 0 && len(array2) == 0 {
		return true
	}

	if len(array1) == 0 || len(array2) == 0 {
		return false
	}

	arrMap := make(map[int]int)

	for i, v := range array1 {
		if v < 0 {
			v = -v
			array1[i] = v
		}

		arrMap[v]++
	}

	for _, v := range array2 {
		root := math.Sqrt(float64(v))
		intRoot := int(root)

		if math.Trunc(root) != root {
			return false
		}

		_, exists := arrMap[intRoot]

		if !exists {
			return false
		}

		arrMap[intRoot]--

		if arrMap[intRoot] == 0 {
			delete(arrMap, intRoot)
		}
	}

	for _, fr := range arrMap {
		if fr != 0 {
			return false
		}
	}

	return true
}

func main() {
	var a1 = []int{121, 144, 19, 161, 19, 144, 19, 11}
	var a2 = []int{11 * 11, 121 * 121, 144 * 144, 19 * 19, 161 * 161, 19 * 19, 144 * 144, 19 * 19}
	fmt.Println(Comp(a1, a2), true)
	a1 = []int{121, 144, 19, 161, 19, 144, 19, 11}
	a2 = []int{11 * 21, 121 * 121, 144 * 144, 19 * 19, 161 * 161, 19 * 19, 144 * 144, 19 * 19}
	fmt.Println(Comp(a1, a2), false)
	a1 = nil
	a2 = []int{11 * 11, 121 * 121, 144 * 144, 19 * 19, 161 * 161, 19 * 19, 144 * 144, 19 * 19}
	fmt.Println(Comp(a1, a2), false)
}
