// https://www.codewars.com/kata/52c31f8e6605bcc646000082/train/go

package kata

func TwoSum(numbers []int, target int) [2]int {
	numsMap := make(map[int]int)

	for i, v := range numbers {
		firstI, ok := numsMap[v]

		if ok == true {
			return [2]int{firstI, i}
		}

		numsMap[target-v] = i
	}

	return [2]int{}
}
