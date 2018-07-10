

// Link to the task : https://www.codewars.com/kata/directions-reduction/train/javascript


// First alternative
function sol (arr) {



    // This will make our work easier
    const opp =  {
        "NORTH" : "SOUTH",
        "WEST" : "EAST",
        "SOUTH" : "NORTH",
        "EAST" : "WEST"
    };

    // Reduce the array using the reduce() function
    // The accumulator (dirs) will start as an empty array
    return arr.reduce((dirs,dir) => {
        
        // Getting the last element at every iteration will help us removing from the inside first 
        if(dirs[dirs.length-1] === opp[dir]) {

            // Remove from the array
            dirs.pop();

        }else {

            // If there was no match, simply push the current element into the array
            dirs.push(dir);
        }

        // Return the accumulator
        return dirs;

    },[]);


}

//-------------------------------------------------------------------------------


// Second alternative
function sol2(arr) {

    // Conver the array into a string in order to use Regular Expressions
    var str = arr.join('');

    // We first want to get rid of the pairs like NORTH - SOUTH , EAST - WEST etc
    var pattern = /NORTHSOUTH|SOUTHNORTH|EASTWEST|WESTEAST/;

    // Remove those pairs
    while(pattern.test(str)) str = str.replace(pattern, ''); 

    // Get the final array by "splitting" the string using the match() funtion
    return str.match(/NORTH|SOUTH|EAST|WEST/g) || []; // Or an empty array if there is no match


}



// First solution
var res = sol(["NORTH", "SOUTH", "SOUTH", "EAST", "WEST", "NORTH", "WEST"]);
console.log("sol 1",res);


// Second solution
var res2 = sol2(["NORTH", "SOUTH", "SOUTH", "EAST", "WEST", "NORTH", "WEST"]);
console.log("sol 2",res2);



// Other examples

Test.assertSimilar(dirReduc(["NORTH", "SOUTH", "SOUTH", "EAST", "WEST", "NORTH", "WEST"]), ["WEST"])
Test.assertSimilar(dirReduc(["NORTH", "WEST", "SOUTH", "EAST"]), ["NORTH", "WEST", "SOUTH", "EAST"])
Test.assertSimilar(dirReduc(["NORTH", "SOUTH", "EAST", "WEST", "EAST", "WEST"]), [])

