// https://www.codewars.com/kata/59c633e7dcc4053512000073/train/go

package kata

import "strings"

func isCons(ch rune) bool {
	return !strings.Contains("aeiou", string(ch))
}

func solve(str string) int {
	maxV := 0
	cons := make(map[rune]int)

	for i := 0; i <= 25; i++ {
		cons[rune('a'+i)] = i + 1
	}

	isSubstr := false
	s := 0

	for _, c := range str + "a" {
		if isCons(c) {
			if !isSubstr {
				isSubstr = true
			}

			s += cons[c]

			continue
		}

		if !isSubstr {
			continue
		}

		if s > maxV {
			maxV = s
		}

		isSubstr = false
		s = 0
	}

	return maxV
}
