
// Link to the task : https://www.codewars.com/kata/5842df8ccbd22792a4000245/solutions/javascript

function expand(num) {

    var output = "";

    
    var div = 1;

    while(num >= div) div *=10;
    
    div = div /10;


    while(num) {

        // Get the main digit
        var digit  = Math.floor(num / div);

        // If the main digit is 0, we'll simply add ""
        output += digit !=0 ? digit * div + " + " : "";

        // Look for the next digits
        num = num % div;

        div = div / 10;

    }

    return output.slice(0,output.length-3);

}

let res = expand(70495);

console.log(res);



// Other examples

Test.assertEquals(expandedForm(12), '10 + 2');
Test.assertEquals(expandedForm(42), '40 + 2');
Test.assertEquals(expandedForm(70304), '70000 + 300 + 4');


