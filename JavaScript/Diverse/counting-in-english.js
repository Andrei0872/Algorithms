// https://www.codewars.com/kata/counting-in-english-one-two-three-dot-dot-dot-to-2-quadrillion-2-000-000-000-000-000/train/javascript

const digits = {
    0: "zero",
    1: "one",
    2: "two",
    3: "three",
    4: "four",
    5: "five",
    6: "six",
    7: "seven",
    8: "eight",
    9: "nine"
},
tenToNineteen = {
    0: "ten",
    1: "eleven",
    2: "twelve",
    3: "thirteen",
    4: "fourteen",
    5: "fifteen",
    6: "sixteen",
    7: "seventeen",
    8: "eighteen",
    9: "nineteen"
},
x10 = {
    2: "twenty",
    3: "thirty",
    4: "forty",
    5: "fifty",
    6: "sixty",
    7: "seventy",
    8: "eighty",
    9: "ninety"
},
names = {
    2: "hundred",
    3: "thousand",
    6: "million",
    9: "billion",
    12: "trillion",
    15: "quadrillion"
}

function numberToEnglish(n) {
let english = "";
let string_version = n.toString();
let point_index = string_version.indexOf('.');
let after_point = point_index !== -1 ? string_version.substr(point_index + 1) : '';
string_version = point_index !== -1 ? string_version.substring(0, point_index) : string_version;  

if(string_version[0] === '-') {
    english += 'negative ';
    string_version = string_version.substr(1);
}

if(n === 0 ) return digits[0];

if(isNaN(n)) throw "NaN";

if(!isFinite(n)) {
    return n > 0 ? 'infinity' : 'negative infinity';
}

if(string_version.length === 1 && point_index === -1) {
    english += digits[string_version[0]];
    return english;
}

let sets = Math.floor(string_version.length / 3);
let remaining = string_version.length % 3;

if(remaining === 1) {
    // abcd - parse `a` using `names` 
    // a (1 % 3 = 1) - sets = 0;
    english += digits[string_version[0]];
    english += sets != 0 ? ' ' + names[sets * 3] : '';
    string_version = string_version.substr(1)
} else if(remaining === 2) {
    // abcde - parse ab; sets = 1
    // ab (2 % 3 = 2) - sets = 0
    english += transform2digit(string_version.substr(0, 2))
    english += sets != 0 ? ' ' + names[sets * 3] : ''
    string_version = string_version.substr(2)
} else {
    // abc = (3 % 3 = 0), but sets = 1
    // abcdef - sets = 2; 
    english += transform3digit(string_version.substr(0, 3))
    english += sets - 1 != 0 ? ' ' + names[(sets - 1) * 3] : ''
    string_version = string_version.substr(3)
    sets--;
}

// [abc]def... get the rest 
for(let i = sets - 1; i >= 0; i--) {    
    if(string_version.substr(0,3) === '000') {
        string_version = string_version.substr(3);
        continue;
    }

    // For example: 30030 -  ​​​​​thirty thousand and thirty​​​​​
    if(i === 0 && string_version[0] === '0') {
        english += ' and'
    }
    
    english += ' ' + transform3digit(string_version.substr(0,3))
    string_version = string_version.substr(0,3)

    if(i !== 0 ) english += ' ' + names[i * 3]
}

// Only points
if(after_point.length !== 0) {
    english += ' point';
    [...after_point].forEach(digit => english += " " + digits[digit] )
}
return english;
}

console.log(numberToEnglish(-6000006)) // ​​​​​thirty thousand and thirty​​​​​

// Utility functions
function transform2digit (digitStr) {
// 01 - parse 1
// 12 - use tenToNineteen
// {2...9} - use x10
// {2...9}{1...9} - use x10 and digit
let textNumber = "";

if(digitStr[0] !== '0') {
    if(digitStr[0] === '1') {
        textNumber += tenToNineteen[digitStr[1]];
    } else {
        textNumber += x10[digitStr[0]];
        if(digitStr[1] !== '0') {
            textNumber += '-' + digits[digitStr[1]];
        }
    }
} else textNumber += digits[digitStr[1]];

return textNumber;
}

function transform3digit (digitStr) {
// 000 - return ''
// 010 - parse 10
// 123 - 1 hundred + 'and' +  transform2digit(23)
// 
let textNumber = "";
let last2_digits = digitStr.substr(1);

if(digitStr === '000') return textNumber;

if(digitStr[0] !== '0') {
    textNumber += digits[digitStr[0]] + ' ' + names[2];
    if(last2_digits !== '00') {
        textNumber += ' and ' + transform2digit(last2_digits);
    }
} else textNumber += transform2digit(last2_digits)

return textNumber;
}



// console.log(numberToEnglish(1), "one", "1 -> one");
// console.log(numberToEnglish(5), "five", "5 -> five");
// console.log(numberToEnglish(10), "ten", "10 -> ten");
// console.log(numberToEnglish(99), "ninety-nine", "numbers betwen 20 and 99 are hyphenated");
// console.log(numberToEnglish(123), "one hundred and twenty-three", "123 -> one hundred and twenty-three");
// console.log(numberToEnglish(1234567899), "one billion two hundred and thirty-four million five hundred and sixty-seven thousand eight hundred and ninety-nine", "1,234,567,899");
