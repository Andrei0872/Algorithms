package main

import (
	"fmt"
	"math"
	"sort"
)

// https://www.codewars.com/kata/511f11d355fe575d2c000001

func TwoOldestAges(ages []int) [2]int {
	max1, max2 := math.MinInt64, math.MinInt64

	for _, v := range ages {
		if v > max1 {
			max2, max1 = max1, v
		} else if v > max2 {
			max2 = v
		}
	}

	return [2]int{max2, max1}
}

func main() {
	// fmt.Println(TwoOldestAges([]int{6, 5, 83, 5, 3, 18}), [2]int{18, 83})
	// fmt.Println(TwoOldestAges([]int{1, 5, 87, 45, 8, 8}), [2]int{45, 87})

	nums := []int{1, 2, 3, 4}

	// =========================

	// sort.Sort(sort.Reverse(sort.IntSlice(nums)))
	// fmt.Println(nums)

	// =========================
	sort.Ints(nums) // Same as `Sort(IntSlice(nums))`

	var n [2]int
	copy(n[:], nums[len(nums)-2:])

	fmt.Println(n)
}
