// https://www.codewars.com/kata/strip-comments/train/javascript

function solution(input, markers) {
    markers = markers.map(m => m === '$' ? '\\$' : m)
    const regex = new RegExp(`(?=${markers.join('|')}).*`, 'g')

    return input
        .replace(regex, full => '')
        .replace(/(\s)(?=\n)/g, full => '')
        .trim()
}
