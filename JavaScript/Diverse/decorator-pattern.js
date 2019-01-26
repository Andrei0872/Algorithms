// https://www.codewars.com/kata/decorator-pattern/train/javascript

class Decorator {
    constructor ({ before, after } = {}) {
        this.before = before;
        this.after = after;
    }

    decorate (fn, ... decoratorArgs) {
        return (... funcArgs) => {
            const result = this.before ?
                fn(... this.before(... decoratorArgs, ... funcArgs)) :
                fn(... funcArgs)

            return this.after ? 
                this.after(... decoratorArgs, result):
                result
        }
    }
}