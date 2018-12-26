
// https: //www.codewars.com/kata/get-all-possible-anagrams-from-a-hash/train/javascript

/*
get_words({
    2 => ["a"],
    1 => ["b", "c"]
}) => ["aabc", "aacb", "abac", "abca", "acab", "acba", "baac", "baca", "bcaa", "caab", "caba", "cbaa"]
*/


function getWords(hash) {
    const letters = [];

    for(let how_many in hash) {
        for(let char of hash[how_many]) {
            letters.push(...Array(~~how_many).fill(char))
        }
    }

    const str = letters.join``;

    return (function permutationFunc(s) {
        if(s.length < 2) return s;

        let permutations = [];

        for(let i = 0; i < s.length; i++) {
            let currentChar = s[i];

            // Avoid duplicates
            if(s.indexOf(currentChar) !== i)
                continue;

            let remainingStr = s.slice(0, i) + s.slice(i + 1, s.length);

            for(let subPerm of permutationFunc(remainingStr)) {
                permutations.push(currentChar + subPerm);
            }
        }
        return permutations.sort();
    })(str)

}

console.log(getWords({
    2: ["a"],
    1: ["b", "c"]
}))
