// https://www.codewars.com/kata/5544c7a5cb454edb3c000047/javascript

function bouncingBall(h, bounce, window) {
    if (h <= 0 || !(bounce > 0 && bounce < 1) || !(window < h)) {
        return -1;
    }

    let seenTimes = 0;

    while (h > window) {
        seenTimes = seenTimes === 0 && 1 || seenTimes + 2;

        h *= bounce;
    }

    return seenTimes;
}


console.log(bouncingBall(3.0, 0.66, 1.5), 3);
console.log(bouncingBall(30.0, 0.66, 1.5), 15);
console.log(bouncingBall(3.0, 1, 1.5), 15);

/*
-- 6
-
-- 5
-
-- 4
-
-- 3
-
-- 2
- 1.5
-- 1
*/