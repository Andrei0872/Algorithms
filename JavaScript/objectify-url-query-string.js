

// Link to the task : https://www.codewars.com/kata/objectify-a-url-query-string/train/javascript
/*
Reasoning : {
    1) First create an empty object
    2) Split the given string by "&" so you can determine where to put every property in the object created above
    3) Split every item by  "=" === parts[1]
    4) Split the first element by "." === parts[0]
    5) Assign the parts[1] to the last element from parts[0]
}
*/

function solve(query) {

    // console.log(query)

    // Define the final object
    const obj = {};

    // Split by "&" in order to determine the properties and values
    query.split("&").map((item) => {

        // Split again, but this time, by "=", in order to determine the value of the last property from parts[0]
        let parts = item.split("=");
        // console.log(parts)   

        // Build the object 
        parts[0].split(".").reduce((acc,item,index,arr) => {

            // Find their place in the final object
            if(!acc[item]) acc[item] =  {};
            
            // If we are at the last element, then we must assign the value to this last element
            if(index === arr.length - 1 ) acc[item] = decodeURIComponent(parts[1]); // Decode an encoded URI 

            return acc[item];
        
        // Start with the final object as the accumulator, so for every iteration a property will be returned
        },obj);

    });

    // console.log(obj)

}

solve("user.name.firstname=Bob&user.name.lastname=Smith&user.favoritecolor=Light%20Blue") 
/*
Expected output : 
{ user: 
   { name: { firstname: 'Bob', lastname: 'Smith' },
     favoritecolor: 'Light Blue' 
    } 
}
*/


