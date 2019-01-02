
/* 
A hotel manager has to process N bookings of rooms for the next season. 
His hotel has K rooms. 
Bookings contain an arrival date and a departure date. 
He wants to find out whether there are enough rooms in the hotel to satisfy the demand.

Inputs:
- First list for arrival time of booking
- Second list for departure time of booking
- Third is K which denotes the count of rooms

Output:
- A boolean which tells whether its possible to make a booking
false means there are not enough rooms for N booking
true means there are enough rooms for N booking
*/

/* 
Example

Inputs:
- arrivals = [1, 3, 5]
- departures = [2, 6, 10]
- K = 1

Output:
false (at day 5, there are 2 guests in the hotel)
*/


function solve(arrivals, departures, K) {
    arrivals.sort();
    departures.sort();

    const len = arrivals.length;
    let index_arriv = 0, index_dep = 0;
    let guests = 0;

    while(index_arriv < len && index_dep < len) {
        if(arrivals[index_arriv] < departures[index_dep]) {
            guests++;
            index_arriv++;

            if(guests > K)
                return false;
        } else {
            guests--;
            index_dep++;
        }
    }

    return true;
}

let arrivals = [1, 3, 5];
let departures = [2, 6, 10];
let K = 1;

console.log(solve(arrivals, departures, K)) // false
