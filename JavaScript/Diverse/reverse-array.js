
// https: //www.codewars.com/kata/the-soul-of-wit-reverse-an-array/train/javascript

// [1, 2, 3] -> [3, 2, 1]

reverse = a => a.map(a.pop, [...a])