

// Generate all combinations

function combinations(k,arr) {

    // Length of the array
    var n = arr.length;

    var output = '';

    function generate(arrSoFar,lastIndex) {

        arrSoFar = arrSoFar || [];

        if(arrSoFar.length == k) {

            arrSoFar.map(x => output += x + ", " );
            output = output.replace(/\,\s+$/g,''); // Get rid of the last comma
            output += "\n";

            // Stop here
            return;
        }

        // Loop through the list
        for(var i = lastIndex + 1 || 0; i < n; i++ ) {
            generate(arrSoFar.concat(arr[i]),i);
        }

    }

    // Call the recursive function
    generate();

    return output;


}



console.log(combinations(3,[10,21,11,15,33]));
console.log("-----------------");
console.log(combinations(3,[1,2,3,4]));
