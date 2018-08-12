

// Generate a sorted singly-linked list

// Node structure
class Node {
    constructor(data) {
        this.data =data;
        this.next = null; // Next node         
    }
}

class List{
    constructor() {
        this.head = null;
        this.tail = null;
    }

    // Create the sorted list
    create (data) { // data will be the information that we'll store in the node

        // Create a new node
        let c = new Node(data);

        // If the list has not been created yet
        if(!this.head) {

            this.head = c;
            
            this.tail = this.head; // Because there is only one node in the list
        }else {
            // The list has already been created


            // Can we insert the node BEFORE the first node ?
            if(data <= this.head.data) {
               
                // Then "c" is going to be the first node in the list
                c.next = this.head;
                this.head = c;

            }else if(data > this.tail.data) {

                // Can we insert the node AFTER the last node ?
                
                // Insert after
                this.tail.next = c;
                this.tail = c;

            }else {
                // We'll insert the node somewhere inside the list

                // Use the node a to loop through the list
                let a = this.head;

                // Start looking after the first node, because we check for the first node above

                // Loop through we find an element that is greater than the current value of "data"
                while(data > a.next.data ) a = a.next; // Keep searching

                // Now we have found the node
                c.next = a.next; // The new node will store the node after the node we stopped at
                a.next =c; // c.data is bigger than a.data, but c.data is less than c.next.data

            }

        } // End of else stmt if the list has already been created

    }

    printList() {
        for(let c = this.head;c;c=c.next) {
            console.log(c.data);
        }
    }


}


// Create a new list
let lst = new List();

// Add some values
lst.create(23);
lst.create(10);
lst.create(19);
lst.create(3);
lst.create(13);
lst.create(10);
lst.create(1);

// See the result
lst.printList(); // Output : 1,3,10,10,13,19,23
