/// What about this as a solution? 

function balanced(str) {

    /// remove all non brackets first and then remove all occurences of ()
    let result = str.replace(/[^\(\)]/g, "").replace(/\(\)/g , "")

    /// if matches is an array that means that match found more
    /// which means we can call balanced on result again
    /// if results length is more than 0 then we have a single bracket
    let d = { matches : result.match(/\(\)+/g) , result }

    /// if matches is null and result.length is 0 then its balanced else not
    return d.matches !== null ? balanced(result) : d.result.length === 0 ? true : false
}

console.log(balanced("(() containing text ( () )")) // false
console.log(balanced("(() ( () )")) // false
console.log(balanced("(() containing text ( () ))")) // true


console.log(balanced("(()()(()))")) // true
console.log(balanced("())()(()")) // false
console.log(balanced("((()())())((")) // false

