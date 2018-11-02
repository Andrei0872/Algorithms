
// https://www.codewars.com/kata/5526fc09a1bbd946250002dc/discuss

function findOutlier(integers) {

    let res = integers.reduce((acc, item) => {
        item % 2 == 0 ? acc["even"].push(item) : acc["odd"].push(item)
        return acc;
    }, {
        "odd": [],
        "even": []
    });

    return res["even"].length == 1 ? res["even"][0] : res["odd"][0]
}

console.log(findOutlier([2, 4, 0, 100, 4, 11, 2602, 36])) // 11
console.log(findOutlier([160, 3, 1719, 19, 11, 13, -21])) // 160

// ==============================================================


function findOutlier2(integers) {
    return integers.slice(0, 3).filter(even).length >= 2 ? integers.find(odd) : integers.find(even);
}

function even(num) {
    return (num % 2 == 0);
}

function odd(num) {
    return !even(num)
}
console.log(findOutlier2([2, 4, 0, 100, 4, 11, 2602, 36])) // 11
console.log(findOutlier2([160, 3, 1719, 19, 11, 13, -21])) // 160

