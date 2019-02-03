// https://www.codewars.com/kata/all-balanced-parentheses/train/javascript

function balancedParens(n) {
    const generated = [];

    (function generate(left, right = 0, result = '') {
        if (left === 0 && right === 0) {
            generated.push(result)
        }
        if (left > 0) {
            generate(left - 1, right + 1, result + '(')
        }
        if (right > 0) {
            generate(left, right - 1, result + ')')
        }
    })(n);

    return generated
}

// console.log(balancedParens(3))
// console.log(balancedParens(0).sort(), [""]);
// console.log(balancedParens(1).sort(), ["()"]);
// console.log(balancedParens(2).sort(), ["(())", "()()"]);
// console.log(balancedParens(3).sort(), ["((()))", "(()())", "(())()", "()(())", "()()()"]);
// console.log(balancedParens(4).sort(), ["(((())))", "((()()))", "((())())", "((()))()", "(()(()))", "(()()())", "(()())()", "(())(())", "(())()()", "()((()))", "()(()())", "()(())()", "()()(())", "()()()()"]);