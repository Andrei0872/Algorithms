
function autocomplete(input, dictionary) {
    input = input.replace(/[^a-z]/g, '')
    return dictionary.filter(word => word.toLowerCase().startsWith(input)).splice(0, 5);
}

console.log(autocomplete('ai', ['airplane', 'airport', 'apple', 'ball'])) // ['airplane','airport']