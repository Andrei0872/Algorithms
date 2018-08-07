
//* Longest sequence of repeated characters in a string
/*
Reasoning : {
    1) We will iterate over the string
    2) We will keep track of the previous character for current iteration
    3) if prevChar === currentChar , we increment a "count" variable
    4) For every iteration, compare count with a variable "maximum"
    5) When we find a new maximum value, store the character
}
*/

function longest_sequence(str) {

    // Maximum length of the longest sequence, initially is 0
    let max = 0

    let prevChar, count = 0,i=0, finalChar

    for(; i < str.length; i++) {

        // if prevChar === currentChar
        if(prevChar === str[i]) {
            count++
        }
        else {
            count = 1 // 1 because we count the current str[i]
        }

        if(count > max) {
            // Store the new maximum value
            max = count 
            finalChar = str[i] // Store the character
        }

        // Always update the prev char
        prevChar = str[i]

    }

    return {"length":max,"character":finalChar}

}



console.log(longest_sequence("ABCDDAEEBBBA")) // {"length ":3,"character":'B'}
console.log(longest_sequence("DDDASDWBAMM")) // {"length ": 3,"character":'D'}
console.log(longest_sequence("abbcdwddddalll")) // {"length ": 4,"character":d}

