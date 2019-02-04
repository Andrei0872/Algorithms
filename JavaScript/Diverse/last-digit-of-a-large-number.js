// https://www.codewars.com/kata/last-digit-of-a-large-number/train/javascript

// b % a
function modulo(a, b) {
    let mod = 0;

    for (let i = 0; i < b.length; i++)
        mod = (mod * 10 + (+b[i])) % a;

    return mod;
}

var lastDigit = function (str1, str2) {
    const lenStr1 = str1.length;
    const lenStr2 = str2.length;

    if (
        lenStr2 === 1 && str2[0] === '0' ||
        lenStr1 === 1 && lenStr2 === 1 &&
        str1[0] === '0' && str2[0] === '0'
    )
        return 1;

    if (lenStr1 === 1 && str1[0] === '0')
        return 0;

    const res = modulo(4, str2);
    const exp = res === 0 ? 4 : res;

    return Math.pow(+str1[lenStr1 - 1], exp) % 10
}

// ======================================================

function lastDigit(str1, str2) {
    return +!+str2 || Math.pow(str1.slice(-1), str2.slice(-2) % 4 || 4) % 10
}

console.log(lastDigit("4", "1")) // 4
console.log(lastDigit("4", "2")) // 6
console.log(lastDigit("9", "7")) // 9
