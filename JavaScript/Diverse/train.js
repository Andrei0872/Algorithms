// https://www.codewars.com/kata/rot13-1/train/javascript

function rot13(message) {

    return [...message].map(chr => {
        const currentChar = chr.charCodeAt(chr[0].toString)
        const lowerCase = currentChar + 13 > 122 ? 97 + currentChar + 12 - 122 : currentChar + 13
        const upperCase = currentChar + 13 > 90 ? 65 + currentChar + 12 - 90 : currentChar + 13
        const newChar = currentChar >= 65 && currentChar <= 90 ?
            upperCase : currentChar >= 97 && currentChar <= 122 ?
            lowerCase : currentChar

        return String.fromCharCode(newChar)
    }).join('')
}


console.log("grfg", rot13("test"))
console.log("Grfg", rot13("Test"))
console.log(rot13("10+2 is twelve"))