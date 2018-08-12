
/**
 * Determine the sum of the keys in a singly-linked list
 *  
 */


// The structure of a node
class Node  {

    constructor(data) {
        this.data = data; // The key value
        this.next = null; // Being a singly-linked list, it only holds the reference to the next node
    }

}


class LinkedList {

    // When we create a new instance of a list object
    constructor() {
        this.head = null; // We initialize the head of the list as being null, because the doesn't have any nodes
        this.tail = null; // The tail of the node, which will be modified every time we add a new node
    }

    // Add a new node
    add(data) { // data - the value of the key

        // Create a new node first
        let newNode =  new Node(data);

        // Check whether has already been created or not
        
        if(!this.head) {

            // The list has NOT been created yet
            this.head = newNode; // The head is the new node added
            this.tail = this.head; // Since it is the first node, it is also the last node

        }else {
            
            // The list has already been created
            this.tail.next = newNode; // Make the connection between the last node and the new node that will be added
            this.tail = newNode; // The new node is now the last in the list    
        }

    }

    getSum() {

        // Temporary node that will help us looping through the list
        let temp = this.head; // It starts with the head of the list

        let sum = 0;

        // Loop through the list
        for(;temp;temp = temp.next) {
            sum += temp.data;
        }

        return sum;

    }
    
    printAll() {

        let temp = this.head

        while(temp) {

            console.log("key : ",temp.data);

            // Switch to the next node
            temp = temp.next;

        }

    }

} // End of the class


// Let's assume we have some user-input values..
let arr = [23,123,90,573,241];

// Create a new object list
let list = new LinkedList();

// Fill the list with the array elements
arr.map((x) => list.add(x));

// Check if everything works fine
list.printAll();

// Get the sum
console.log("sum : ",list.getSum()); // Expected : 1050
