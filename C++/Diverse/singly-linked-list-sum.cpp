
// Determine the sum of all keys in a linked list

#include <iostream>

using namespace std;

struct nod {
   
   int inf;
   nod *next;

};

nod *first, *last;

void add(int data ) {
   
    // Create a new node
    nod *c =  new nod;
    c->inf = data;
    if(!first) {
      // If the list has not been created yet
      first = c;
      last = c;
      last->next = NULL;
    }else {
      // The list has already been created
      last->next = c;
      last = c;
      last->next =  NULL;
    }
   
}

// Print the keys of the list
void print() {
   for(nod*c = first;c;c=c->next) {
      cout << c->inf;
   }
}

// Get the sum
int getSum() {
   int s=0;
   for(nod*c = first;c;c=c->next) 
      s +=c->inf;
      
   return s;
}

int main () {
    
    // Add some elements
    add(2);
    add(3);
    add(4);
    
    print();
    
    cout << endl;
    cout << getSum();
    return 0;

}
