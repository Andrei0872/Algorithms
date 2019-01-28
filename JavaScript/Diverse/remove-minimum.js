// https://www.codewars.com/kata/remove-the-minimum/train/javascript

function removeSmallest (nums) {
    if (!nums.length)
        return []

    let numbers = [...nums]
    const minVal = Math.min(...numbers)
    const minIndex = numbers.findIndex(num => num === minVal)
    numbers.splice(minIndex, 1)

    return numbers;
}

// ==============================================

function removeSmallest (nums) {
    const minVal = Math.min(...nums)
    const minIndex = nums.indexOf(minVal)

    return nums.filter((num, index) => index !== minIndex)
}