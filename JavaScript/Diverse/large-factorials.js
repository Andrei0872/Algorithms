// https://www.codewars.com/kata/large-factorials/train/javascript

function multiply(num, res) {
    let carry = 0;

    for (const index in res) {
        const prod = res[index] * num + carry;
        res[index] = prod % 10;
        carry = Math.floor(prod / 10);
    }

    while (carry) {
        res.push(carry % 10);
        carry = Math.floor(carry / 10);
    }
}

function factorial(n) {
    const res = [];
    res[0] = 1;

    for (let i = 2; i <= n; i++)
        multiply(i, res)

    return res.reverse().join('')
}

console.log(factorial(1), '1', '1!');
console.log(factorial(5), '120', '5!');
console.log(factorial(9), '362880', '9!');
console.log(factorial(15), '1307674368000', '15!');