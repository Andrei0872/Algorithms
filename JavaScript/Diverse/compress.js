// https://leetcode.com/problems/string-compression/submissions/

const compress = function (chars) {
  let i = chars.length - 1;

  while (i >= 0) {
    let seqLen = 1;

    while (chars[i] === chars[i - 1]) { seqLen++; i--; }

    if (seqLen === 1) { 
      i--;
      continue; 
    }

    chars.splice(i + 1, seqLen - 1, ...`${seqLen}`.split(''));
    i--;
  }

  return chars.length;
};