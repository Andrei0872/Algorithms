
// Track the current minimum value in stack

/*
We will use 2 stacks:
- 1 in which we will insert elements 
- 1 for tracking the current minimum element in the above stack
*/

class CurrentMin {

    constructor() {
        this.currenStack = []
        this.trackStack = []
    }

    push(elem) {

        // Push to the current stack every time this method is called
        this.currenStack.push(elem);

        // If there is only one element, that's also the current minimum value
        if(this.currenStack.length === 1) {
            this.trackStack.push(elem);
        }
        // If "elem" is less than the current minimum value, we update the trackStack
        if(elem < this.trackStack[this.trackStack.length - 1]) {
            this.trackStack.push(elem);
        }else {
            // Otherwise push the current minimum value
            this.trackStack.push(this.trackStack[this.trackStack.length-1]);
        } 
    }

    getCurrentMin() {
        return this.trackStack[this.trackStack.length -1 ];
    }
    
}

let obj = new CurrentMin();
obj.push(30);
console.log(obj.getCurrentMin()); // 30
obj.push(10);
console.log(obj.getCurrentMin()); // 10 
obj.push(5);
console.log(obj.getCurrentMin()); // 5
obj.push(12);
console.log(obj.getCurrentMin()); // 5
obj.push(8);
console.log(obj.getCurrentMin()); // 5
