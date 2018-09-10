

//* Generate Hashtag

// https://www.codewars.com/kata/the-hashtag-generator/javascript

function generateHashtag(str) {

    if(!str.trim()) return false;

    const res =  "#" + str
    .replace(/^\w/, function (s) {return s.toUpperCase()}) // Capitalize first letter
    .replace(/\s+([a-z])/g,function(match,$1) {console.log(match);return $1.toUpperCase();}) // Capitalize first letters
    .replace(/\s+/g,''); // Ignore whitespaces
    
    return res.length >140 ? false : res;
       
   }   
   

console.log(generateHashtag(""), false)
console.log(generateHashtag(" ".repeat(200)), false);
console.log(generateHashtag("Do We have A Hashtag"), "#DoWeHaveAHashtag")
console.log(generateHashtag("Codewars"), "#Codewars")
console.log(generateHashtag("Codewars Is Nice"), "#CodewarsIsNice")
console.log(generateHashtag("Codewars is nice"), "#CodewarsIsNice", "Should capitalize first letters of words.")
console.log(generateHashtag("code" + " ".repeat(140) + "wars"), "#CodeWars")
console.log(generateHashtag("Looooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooong Cat"), false, "Should return false if the final word is longer than 140 chars.")
console.log(generateHashtag("a".repeat(139)), "#A" + "a".repeat(138), "Should work")
console.log(generateHashtag("a".repeat(140)), false, "Too long")
