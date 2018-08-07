
// Given a set of round brackets, determine if the brackets are balanced

// (()()(())) - true
// ())()(() - false
// ((()())())(( - false

/*
Reasoning : {
    1) We will keep on deleting pairs of brackets : () - and here comes the "do while"
    2) If the string's length is 0 at the end, it means the brackets are balanced
}
*/

function balanced(s) {
    // Convert to array so we can use the "splice" function
    s = s.split('');
    let n,m;
    do{
        // Get the length before doing any deletion
        n = s.length;
        for(let i = n-1; i>=0; i--) {
            // If we find a pair of brackets
            if(s[i] == '(' && s[i+1] == ')') {
                // Delete the pair
                s.splice(i,2);
            }
        }
        // Get the length after deletion
        m = s.length;
    }while(m !=n); // Keep repeating until there is nothing to delete 

    // If the length is 0, is means the brackets are balanced
    return s.length == 0 ? true:false;

}

console.log(balanced("(()()(()))")) // true
console.log(balanced("())()(()")) // false
console.log(balanced("((()())())((")) // false

