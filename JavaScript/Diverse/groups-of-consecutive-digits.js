// Split a number in groups of consecutive digits

// 1234679 => [[1, 2, 3, 4], [6,7], [9]]
// 1235689 => [[1, 2, 3], [5, 6], [8, 9]]

function splitNum (num) {
    let lastAddedDigit = null;
    
    return `${num}`.split``
        .map(Number)
        .reduce((memo, digit) => {
            lastAddedDigit === null || lastAddedDigit + 1 !== digit
                ? memo.push([digit]) 
                : memo[memo.length - 1].push(digit)

            lastAddedDigit = digit;
            
            return memo;
        }, [])
}


console.log(splitNum(1234679), [[1, 2, 3, 4], [6, 7], [9]])
console.log(splitNum(1235689), [[1, 2, 3], [5, 6], [8, 9]])