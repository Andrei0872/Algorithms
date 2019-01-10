// https: //www.codewars.com/kata/multiplying-numbers-as-strings/train/javascript

function replacements(num) {
    return num.replace(/\-|\./, '')
        .split ``
        .reverse()
}

function multiply(a, b) {
    const sign = /^\-/.test(a) || /^\-/.test(b) ? '-' : ''
    let dot_a = a.indexOf('.')
    let dot_b = b.indexOf('.')
    const dotIndex = (dot_a !== -1 ? a.length - dot_a - 1 : 0) +
        (dot_b !== -1 ? b.length - dot_b - 1 : 0)

    a = replacements(a)
    b = replacements(b)

    let arr = []
    for (let i = 0; i < a.length; i++) {
        for (let j = 0; j < b.length; j++) {
            arr[i + j] = arr[i + j] ? (arr[i + j] += a[i] * b[j]) : (arr[i + j] = a[i] * b[j])
            arr[i + j + 1] = Math.floor(arr[i + j] / 10) + (arr[i + j + 1] || 0)
            arr[i + j] %= 10
        }
    }

    let result = arr.reverse()

    if (dotIndex)
        result.splice(result.length - dotIndex, 0, '.') // Add .

    result = result.join('')
        .replace(/\.$|^0+/g, '')
    return !result || result === '0' ? '0' : sign + result
}


// console.log(multiply("2", "3"), "6");
// console.log(multiply("30", "69"), "2070");
// console.log(multiply("11", "85"), "935");
// console.log(multiply("2", "0"), "0");
// console.log(multiply("0", "30"), "0");
// console.log(multiply("0000001", "3"), "3");
// console.log(multiply("1009", "03"), "3027");
// console.log(multiply("98765", "56894"), "5619135910");
// console.log(multiply("1020303004875647366210", "2774537626200857473632627613"), "2830869077153280552556547081187254342445169156730");
// console.log(multiply("58608473622772837728372827", "7586374672263726736374"), "444625839871840560024489175424316205566214109298");
// console.log(multiply("9007199254740991", "9007199254740991"), "81129638414606663681390495662081");