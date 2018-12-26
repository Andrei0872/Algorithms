

// https: //www.codewars.com/kata/tree-depth/train/javascript

function isObject(val) {
    return ({}).toString.call(val) === '[object Object]'
}

function recordDepth(tree, d = 0) {
    if(!isObject(tree)) return null;
    tree.depth = d;

    for(let prop in tree) {
        if(isObject(tree[prop])) recordDepth(tree[prop], d + 1);
    }

    return tree;
}



let tree = { a: 1, b: 2, c: { d: 3 }};
console.log(recordDepth(tree)) // { a: 1, b: 2, c: { d: 3, depth: 1 }, depth: 0 }

let notAnObject = []
console.log(recordDepth(notAnObject)) // null

