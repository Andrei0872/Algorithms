
function decompose2(n) {

    // Get the 2 numbers
    let [a,b] = isNaN(n) ? n.split('/').map(Number) : [Number(n),1];
    let res = [];


    if(a > b) {
        // b >> 0 -  get rid of decimal part
        //? << 0 might get the same result
        res.push(String(a/b << 0));
        a %= b;
    }


    while(a > 0) {
        let dv = Math.ceil(b/a);
        res.push('1/' + dv);
        [a,b] = [a*dv-b,b*dv];
    }   
    return res
}

console.log(decompose2("2/3")) // [ '1/2', '1/6' ]
console.log(decompose2("0.66")) // [ '1/2','1/7','1/59','1/5163','1/53307975','1/65654145855032260' ]
console.log(decompose2("4/3")) // ['1','1/3']