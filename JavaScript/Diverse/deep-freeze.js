
// https://www.codewars.com/kata/deep-freeze/train/javascript

Object.deepFreeze = function (object) {
    Object.freeze(object);
    
    for(let key in object) {
        if (typeof object[key] === 'object') 
            Object.deepFreeze(object[key])
    }
}

var a = { b: [42, { x: 9 }] };
Object.deepFreeze(a);

a.b = 42;
console.log(a.b, [42, { x: 9 }]);

a.b[1] = 42;
console.log(a.b[1], { x: 9 });
