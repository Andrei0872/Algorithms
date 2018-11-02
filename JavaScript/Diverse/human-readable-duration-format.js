

// Link to the task : https://www.codewars.com/kata/52742f58faf5485cae000b9a

function formatDuration(seconds) {

    // Useful to determine time units
    const secIn = {
        "minutes" : 60,
        "hours" : 60 * 60,
        "days": 60 * 60 * 24,
        "years" : 60 * 60 * 24 *365
    };

    
    if(seconds === 0 ) {
        return 'now';
    }


    // The units 
    let years = 0,
        days = 0,
        hours = 0,
        minutes = 0;


    // The seconds will be what's left after finding out the other time units
    let sec = seconds;
     

    // Determine the number of time units
    function findTimeUnits (unit) {
        let cnt = 0;
        while(sec >= secIn[unit]) {
            sec -= secIn[unit];
            cnt++;
        }
        return cnt;
    }

    // Find out time units
    // The order is important!!
    years = findTimeUnits("years");
    days = findTimeUnits("days");
    hours = findTimeUnits("hours");
    minutes = findTimeUnits("minutes");


    // Return the formatted string
    return ((years != 0 ? years == 1 ? years + " year" : years + " years" : '') + 
               (years !=0 && days !=0 ? ", " : "" !=0 && hours !=0 ? ", " : "") + (days != 0 ? days == 1 ? days + " day" : days + " days" : '') + 
               (days !=0 && hours !=0 ? ", " : "") + (hours != 0 ? hours == 1 ? hours + " hour" : hours + " hours" : '') +
               (hours !=0 && minutes !=0 ? sec ==0 ? "and " : ", " : "") + (minutes != 0 ? minutes == 1 ? minutes  +  " minute ": minutes + " minutes " : '') + 
               (minutes !=0 && sec !=0 ? "and " : "") + (sec !=0 ?  sec == 1 ? sec + " second" : sec + " seconds" : "")).trim('');  
}



console.log(formatDuration(1)); //, "1 second");
console.log(formatDuration(62)); //, "1 minute and 2 seconds");
console.log(formatDuration(120)); //, "2 minutes");
console.log(formatDuration(3600)); //, "1 hour");
console.log(formatDuration(3662)); //, "1 hour, 1 minute and 2 seconds");
  
