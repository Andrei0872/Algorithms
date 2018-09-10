

//* Find the capitals

// https://www.codewars.com/kata/find-the-capitals-1/train/javascript

// Using reduce
function capitals(word) {
    res = [];
    Array.prototype.reduce.call(word, function (acc,item,index) {
        console.log(index)
        console.log(item)
        if(item === item.toUpperCase())
            acc.push(index)
        
            return acc;
    },res);
    return res;
}
console.log(capitals('CodEWaRs'), [0,3,4,6] );



// Using filter & map
function capitals2(word) {

   return word.split('').map((letter,index) => ({
        letter,
        index
    }))
    .filter(({letter}) => letter === letter.toUpperCase())
    .map(({index}) => index)
    
}
console.log(capitals2('CodEWaRs'), [0,3,4,6] );


// Using regex
function capitals3(word) {

    return word.split('').map((letter,index) => ({
         letter,
         index
     }))
     .filter(({letter}) => letter.match(/[A-Z]/))
     .map(({index}) => index)
     
 }
 console.log(capitals3('CodEWaRs'), [0,3,4,6] );
 

