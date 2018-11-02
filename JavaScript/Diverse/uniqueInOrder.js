
function uniqueInOrder(iterable) {
    if(iterable.length === 0 )
        return;
    return [...iterable].reduce((acc,elem,i) => {
        i < 1
        ? acc.push(elem)
        : elem !== iterable[i-1] 
        ? acc.push(elem)
        : null; 

        return acc;
    },[]);
}
console.log(uniqueInOrder('AASJJSDDSDD')) //  [ 'A', 'S', 'J', 'S', 'D', 'S', 'D' ]

//======================================================

function uniqueInOrder2(iterable) {
    const uniqueArr = [];
    let prev;

    for(let i =0 ; i < iterable.length ; i++) {
        prev !== iterable[i] ? uniqueArr.push(prev = iterable[i]) : null;
    }

    return uniqueArr;
}
console.log(uniqueInOrder2('AASJJSDDSDD')) //  [ 'A', 'S', 'J', 'S', 'D', 'S', 'D' ]

