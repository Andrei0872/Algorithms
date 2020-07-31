const generateAsciiBox = (word, hSpace = 2, vSpace = 1) => {
  const defaultHorizontalLen = 1;

  const totalHorizontalLen = word.length + 2 * hSpace;
  const totalVerticalLen = defaultHorizontalLen + 2 * vSpace;

  const horizontalDashedLine = '-'.repeat(totalHorizontalLen + 2); // 2 - the left & right borders
  const horizontalEmptyLine = ' '.repeat(totalHorizontalLen);
  const emptySpace = ' '.repeat(hSpace);

  const isWordLine = idx => idx === Math.floor(totalVerticalLen / 2);

  let result = horizontalDashedLine + '\n';

  for (let i = 0; i < totalVerticalLen; i++) {
    const crtLineContent = '|' + (isWordLine(i) ? emptySpace + word + emptySpace : horizontalEmptyLine) + '|';

    result += crtLineContent + '\n';
  }

  result += horizontalDashedLine;

  return result;
}

console.log(generateAsciiBox('andrei'))
/*
------------
|          |
|  andrei  |
|          |
------------
*/
