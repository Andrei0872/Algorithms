// https: //www.codewars.com/kata/string-incrementer/train/javascript

function incrementString(strng) {
    if (isNaN(+(strng[strng.length - 1])))
        return strng + 1;

    return strng.replace(/(0*)([0-9]+$)/, function (full, first, second) {
        let next = +(second) + 1

        return next.toString().length > second.length ? first.slice(0, -1) + next : first + next;
    })

}

// Another Solution

function incrementString(strng) {
    return strng.replace(/([0-8]?)(9*)$/, function (full, first, second) {
        first
        return +first + 1 + second.replace(/9/g, '0')
    })
}

console.log(incrementString("foobar000"), "foobar001");
console.log(incrementString("foo"), "foo1");
console.log(incrementString("foobar001"), "foobar002");
console.log(incrementString("foobar99"), "foobar100");
console.log(incrementString("foobar099"), "foobar100");
console.log(incrementString(""), "1");