
// Reverse a linked list

class Node {
    constructor(value) {
        this.value = value
        this.next = null
    }
}

class List {
    constructor() {
        // Initialize the first node and the last node
        this.first = null;
        this.last = null;
    }

    add(value) {

        // If the list has not been created yet
        if(!this.first) {
            // Create the list by creating the first node
            this.first = new Node(value);
            this.last = this.first;
        } else {

            // The list has already been created
            let nodeToAdd = new Node(value);
            this.last.next = nodeToAdd;
            // The node added is now the last node
            this.last = nodeToAdd;
        }
    }

    getFirstNode() {
        return this.first;
    }

    display(nodeToStart) {
        let temp = nodeToStart;
        for(;temp;temp = temp.next) {
            console.log(temp.value)
        }
    }    

    reverse() {
        let current = this.first,
            next = null,
            prev = null;

        while(current) {

            next = current.next;
            // The current node holds the prev node address
            current.next = prev;
            prev = current;
            current = next
        }
        return prev;
    }

    reverseRec(nodeToStart) {
        // Base case
        if(!nodeToStart || !nodeToStart.next) {
            return nodeToStart;
        }

        // At first, result will be the last node in the list
        let result = this.reverseRec(nodeToStart.next);

        // nodeToStart is the node before "result"
        // nodeToStart holds the address of the next node
        // Make the "result" node to hold the address of this "nodeToStart"
        nodeToStart.next.next = nodeToStart;

        // nodeToStart is nos the last element
        nodeToStart.next = null;

        return result;
    }

}


const list =  new List();
list.add(1);
list.add(2);
list.add(3);
list.add(4);

list.display(list.getFirstNode()); // 1 2 3 4

// reverse() returns the last node which is now the first node in the list
let firstNode  = list.reverse();

list.display(firstNode); // 4 3 2 1

list.display(list.reverseRec(firstNode)) // 1 2 3 4 
