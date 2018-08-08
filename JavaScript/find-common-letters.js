
// Find common letters of 2 given strings

function commonLetters (s1,s2) {
    const letters1 = {}
    s1.split('').reduce((freq,character)=> {
        freq[character] = -~freq[character];
        return freq;
    },letters1);

    const letters2 = {}
    s2.split('').reduce((freq,character)=> {
        freq[character] = -~freq[character];
        return freq;
    },letters2); 

    let ch;
    for(var i =0; i <=25; i++ ) {
        ch = String.fromCharCode(i + 97);
        if(letters1[ch] && letters2[ch]) {
            console.log(ch) // a, d, m, s
        }
    }

}

console.log(1)
let s1 = "asdajdasm";
let s2 = "dasmkmkqsk";
commonLetters(s1,s2);

