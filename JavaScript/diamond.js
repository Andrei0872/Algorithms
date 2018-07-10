
/*

    Link to the task : http://www.codewars.com/kata/give-me-a-diamond/solutions?show-solutions=1

    Example : {
        n = 5 
              *
             ***
            *****
             ***
              *

    }

*/

function diamond (n) {


    // Check if we can get that diamond
    if(n % 2 == 0 || n < 1 ) return null;

    // Number of spaces
    var x = 0; // Initially is 0

    var add; // Here we will store the other lines

    // First get the full line
    var fullLine = line(x,n); // x - number of spaces; n - number of stars

    //* We will fill the sides of the diamond simultaneously

    // Get that diamond!
    while((x+=2) < n) {

        // The number of spaces will be x/2
        add = line(x/2,n-x); // The number of stars will be n-x because on each new line -2 stars
        
        fullLine = add + fullLine + add;

    }

    return fullLine;

}

// Returns a string
function line(spaces, stars) {

    return repeat(" ",spaces) + repeat("*",stars) + "\n";

}

// Returns also a string
function repeat(stringToRepeat,numberOfRepeats) {
    
    // +1 - because we will use join()
    return Array(numberOfRepeats+1).join(stringToRepeat); // Example: Array(5).join("*") - ****

}

