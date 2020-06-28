package main

import (
	"fmt"
	"strings"
)

func DuplicateEncode(word string) string {
	word = strings.ToLower(word)
	res := ""
	freqMap := make(map[rune]int)

	for _, ch := range word {
		freqMap[ch]++
	}

	for _, ch := range word {
		var newCh rune

		if freqMap[ch] > 1 {
			newCh = ')'
		} else {
			newCh = '('
		}

		res += string(newCh)
	}

	return res
}

func main() {
	fmt.Println(DuplicateEncode("din"), "(((")
	fmt.Println(DuplicateEncode("recede"), "()()()")
	fmt.Println(DuplicateEncode("(( @"), "))((")
	fmt.Println(DuplicateEncode("Success"), ")())())")
}
