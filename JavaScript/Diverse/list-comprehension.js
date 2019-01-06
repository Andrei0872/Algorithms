
// https: //www.codewars.com/kata/list-comprehensions/train/javascript

var listComprehension = function (str) {
    let matches = str.match(/^(.*)for(.*)in(.*)$/)
    let iterator = matches[1].replace('[', '').trim();
    let varName = matches[2].trim()
    arr = matches[3].replace('/]/', '').slice(0, -1).trim()

    if (arr === '[]')
        return [];

    let functionContent = `
          arr = ${arr}
        `
    new Function(undefined, undefined, functionContent)()

    // Just print the array
    if (iterator === varName) {
        return arr;
    }

    if (iterator.includes('function')) {
        let operation = iterator.replace(new RegExp(`${varName}`, 'g'), 'param')

        let functionContentEach = `
                return ${operation}
            `

        return arr.map(new Function('param', functionContentEach));
    }

    if (iterator.includes(`${varName}.`)) {
        let operation = iterator.replace(new RegExp(`${varName}`, 'g'), 'param')

        let functionContentEach = `
                return ${operation}
            `

        return arr.map(new Function('param', functionContentEach));
    }

    // Getting rid of the variable name
    let opeartion = iterator.replace(new RegExp(`${varName}`, 'g'), '')
    console.log(opeartion)

    let functionContentEach = `
            return ${opeartion}param
        `
    return arr.map(new Function('param', functionContentEach));

};



console.log(listComprehension("[x for x in []]"), [])
console.log(listComprehension("[5000*x for x in [1,2,3]]"), [5000, 10000, 15000]);
console.log(listComprehension("[(function(z){return z-2;})(abcd+5) for abcd in [1,2,3]]"), [4, 5, 6]);
console.log(listComprehension("[x.replace(/abc/g,'123') for x in ['abc','def','ghi','iasdfbcabc'].map(function(a){return 'abc'+a+'abc';})]"), ['123123123', '123def123', '123ghi123', '123iasdfbc123123'])
