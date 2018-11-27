
// https://www.codewars.com/kata/56a1c63f3bc6827e13000006/train/javascript



let Node = function (value,s) {
    this.dup = 1;
    this.val = value;
    this.sum = s;
    this.left = null;
    this.right = null;
}

function insert(val, node, res, index, sum) {
    if(node === null ) {
        node = new Node(val, 0);
        res[index] = sum;
    } else if(node.val === val) {
        node.dup++;
        res[index] = sum + node.sum;
    } else if(node.val > val) {
        node.sum++; 
        node.left = insert(val,  node.left, res, index, sum);
    } else {
        node.right = insert(val, node.right, res, index, node.sum + node.dup + sum);
    }

    return node;
}

function smaller(arr) {
    let node = null;
    let res = [];

    for(let i = arr.length - 1; i >= 0; i--) {    
        node = insert(arr[i], node, res, i, 0);
    }

    return res;
}

console.log(smaller([5, 4, 3, 2, 1]), [4, 3, 2, 1, 0]);
console.log(smaller([1, 2, 3]), [0, 0, 0]);