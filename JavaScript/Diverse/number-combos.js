

// https: //www.codewars.com/kata/find-all-possible-number-combos-that-sum-to-a-number/train/javascript

function combos(n, s = n, index = 1, arr = [], res = []) {
    if (s < 0) return;

    if (s === 0 && arr.length) {
        if (!res.find(a => JSON.stringify(a.sort((a, b) => a - b)) === JSON.stringify(arr.sort((a, b) => a - b))))
            res.push([...arr])
        arr = []
        return;
    }

    for (let i = index; i <= n; i++) {
        arr.push(i)
        combos(n, s - i, i, arr, res);
        arr.pop(i);
    }

    return res
}

function combos2(n) {
    const results = [];

    (function temp(n, s = n, arr = []) {
        if(s === 0 ) {
            results.push(arr)
            return;
        }

        for(let i = Math.min(n, s); i >= 1; i--) {
            temp(n, s - i, [...arr, i]);
        }
    })(n);

    return results;
}

// combos(3) => [ [ 3 ], [ 1, 1, 1 ], [ 1, 2 ] ]
console.log(combos2(3)) // [ [ 3 ], [ 1, 1, 1 ], [ 1, 2 ] ]
