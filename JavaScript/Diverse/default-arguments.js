
// https://www.codewars.com/kata/default-arguments/train/javascript

function defaultArguments(func, params) {
    const defaultArgs = []
    const currentArgNames = func.toString()
        .replace(/[/]{2}.*$/mg, '') // Single line comments
        .replace(/\s/g, '')
        .replace(/[/][*][^/*]*[*][/]/g, '') // Multi-line comments
        .split('(')[1]
        .split(')')[0]
        .split(',');

    if (!this.cache || currentArgNames[0] !== '') 
        this.cache = currentArgNames

    this.cache.forEach((param, index) => {
        const defaultParam = params[param]

        defaultParam ? defaultArgs[index] = defaultParam : null
    });

    return function () {
        const funcArgs = [... arguments]
        const currentArgs = [... defaultArgs]
        
        funcArgs.forEach((funcArg, i) => {
            currentArgs[i] = funcArg
        })

        return func.apply(null, currentArgs)
    }
}

function add(a,b) { return a+b; }

var add_ = defaultArguments(add,{b:9});
console.log(add_(10), 19);
console.log(add_(10,5), 15);
var add_ = defaultArguments(add_,{ b:3 });
console.log(add_(10), 13);
console.log(defaultArguments(add_,{b:3,a:2})(9,9))
