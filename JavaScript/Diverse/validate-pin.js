
// https: //www.codewars.com/kata/regex-validate-pin-code/train/javascript

function validatePIN(pin) {
    return /^(\d{4}|\d{6})$/.test(pin)
}

console.log(validatePIN("1234") === true)
console.log(validatePIN("12345") === false)
console.log(validatePIN("a234") === false)