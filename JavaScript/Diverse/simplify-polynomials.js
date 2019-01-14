// https: //www.codewars.com/kata/simplifying-multilinear-polynomials/train/javascript

function simplify(poly) {
    const store = {}

    poly.match(/[+-]?[^+-]+/g).forEach(item => {
        let vars = item.match(/[a-z]+/)[0]
        let num = item.replace(vars, '')

        vars = vars.split('')
            .sort()
            .join('')

        num = ~~(/\d/.test(num) ? num : num + '1')

        store[vars] = (store[vars] || 0) + num
    })

    return Object.keys(store)
        .filter(ind => store[ind])
        .sort((a, b) => a.length - b.length || (a < b ? -1 : 1))
        .map((item, i) => ({
            sign: store[item] < 0 ? '-' : i > 0 ? '+' : '',
            num: Math.abs(store[item]),
            item
        }))
        .map(obj => obj.sign + (obj.num === 1 ? '' : obj.num) + obj.item)
        .join('')
}

console.log(simplify("dc+dcba"), "cd+abcd")
console.log(simplify("2xy-yx"), "xy")
console.log(simplify("-a+5ab+3a-c-2a"), "-c+5ab")
console.log(simplify("-abc+3a+2ac"), "3a+2ac-abc")
console.log(simplify("xyz-xz"), "-xz+xyz")