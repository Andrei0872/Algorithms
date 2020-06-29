// https://www.codewars.com/kata/58f5c63f1e26ecda7e000029/train/go

package kata

func wave(words string) []string {
	if len(words) == 0 {
		return []string{}
	}

	res := []string{}

	for i, ch := range words {
		if ch == ' ' {
			continue
		}

		res = append(res, words[:i]+string(ch-32)+words[i+1:])
	}

	return res
}
