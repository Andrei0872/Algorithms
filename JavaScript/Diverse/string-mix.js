
// https: //www.codewars.com/kata/strings-mix/train/javascript

function mix(s1, s2) {
    const counter = str => {
        return str.replace(/[^a-z]/g, '')
            .split('')
            .sort()
            .reduce((store, key) => {
                store[key] = 1 + (store[key] || 0)
                return store
            }, {})
    }

    s1 = counter(s1)
    s2 = counter(s2)

    const keys = new Set([...Object.keys(s1), ...Object.keys(s2)])
    const res = [];

    keys.forEach(key => {
        let cnt1 = s1[key] || 0;
        let cnt2 = s2[key] || 0;

        let maxCnt = Math.max(cnt1, cnt2);

        if (maxCnt > 1) {
            let from = [1, '=', 2][Math.sign(cnt2 - cnt1) + 1]
            let str = [...Array(maxCnt)].map(_ => key).join('')
            res.push(`${from}:${str}`)
        }
    });

    return res.sort((x, y) => y.length - x.length || (x < y ? -1 : 1)).join('/')
}


let s1 = "my&friend&Paul has heavy hats! &"
let s2 = "my friend John has many many friends &"

console.log(mix(s1, s1)) // =:aaaa/=:hhh/=:ee/=:ss/=:yy​​​​​