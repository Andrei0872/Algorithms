// https://www.codewars.com/kata/find-the-smallest/train/javascript

function smallest(n) {
    Array.prototype.move = function (from, to) {
        this.splice(to, 0, this.splice(from, 1)[0])
        return this
    }

    const len = `${n}`.length;
    const result = new Map()

    for (let i = 0; i < len; i++) {
        for (let j = 0; j < len; j++) {
            const newNumber = `${n}`.split('').move(i, j).join('');
            !result.has(+newNumber) && result.set(+newNumber, [i, j])
        }
    }

    const minVal = Math.min(...result.keys())
    return [minVal, ...result.get(minVal)]
}
console.log(smallest(261235), [126235, 2, 0]);
console.log(smallest(209917), [29917, 0, 1]);
console.log(smallest(285365), [238565, 3, 1]);
console.log(smallest(269045), [26945, 3, 0]);
console.log(smallest(296837), [239687, 4, 1]);