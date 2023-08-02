package main

import (
	"fmt"
	"reflect"
)

type ListNode struct {
	Val  int
	Next *ListNode
}

func isPalindrome(head *ListNode) bool {
	var valuesUntilMiddle []int

	normalPtr := head
	fastPtr := head
	var middlePtr *ListNode
	listLen := 1

	for true {
		valuesUntilMiddle = append(valuesUntilMiddle, normalPtr.Val)

		middlePtr = normalPtr

		normalPtr = normalPtr.Next
		fastPtr = fastPtr.Next
		listLen += 1

		if reflect.ValueOf(fastPtr).IsZero() {
			listLen -= 1
			break
		}

		if !reflect.ValueOf(fastPtr.Next).IsZero() {
			fastPtr = fastPtr.Next
			listLen += 1
		} else {
			break
		}
	}

	fmt.Println(middlePtr.Val)
	if listLen%2 == 0 {
		middlePtr = middlePtr.Next
	}

	valuesLen := len(valuesUntilMiddle)
	for !reflect.ValueOf(middlePtr).IsZero() {
		if middlePtr.Val != valuesUntilMiddle[valuesLen-1] {
			return false
		}

		middlePtr = middlePtr.Next
		valuesLen--

		if valuesLen < 0 {
			valuesLen = 0
		}
	}
	return true
}

func main() {
	/*
		1 2 2 1
		*
		*
			*
				*
				*
						*
	*/

	/*
		1 2 3 2 1
		*
		*
			*
				*
				*
						*
	*/

	l1 := ListNode{1, &ListNode{2, &ListNode{2, &ListNode{1, nil}}}}
	// l1 := ListNode{1, &ListNode{2, &ListNode{3, &ListNode{2, &ListNode{1, nil}}}}}

	fmt.Println(isPalindrome(&l1))
}


