// https://www.codewars.com/kata/take-a-ten-minute-walk/train/javascript

function isValidWalk(walk) {
    if (walk.length !== 10)
        return false;

    const directions = {
        n: 's',
        s: 'n',
        w: 'e',
        e: 'w',
    };

    let stack = [];

    for (let value of walk) {
        if (!stack.length || directions[stack[stack.length - 1]] !== value)
            stack.push(value);
        else stack.pop()
    }

    return !stack.length
}

console.log(isValidWalk(['n', 's', 'n', 's', 'n', 's', 'n', 's', 'n', 's']), 'should return true');
console.log(isValidWalk(['w', 'e', 'w', 'e', 'w', 'e', 'w', 'e', 'w', 'e', 'w', 'e']), 'should return false');
console.log(isValidWalk(['w']), 'should return false');
console.log(isValidWalk(['n', 'n', 'n', 's', 'n', 's', 'n', 's', 'n', 's']), 'should return false');
