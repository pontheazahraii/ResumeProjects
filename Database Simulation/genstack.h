#ifndef GENSTACK_H
#define GENSTACK_H

#include "linkedlist.h"

/* The GenStack class */
template <typename T>
class GenStack{
    private:
    /* The top of the stack */
    int top;

    public:
    GenStack();
    ~GenStack();

    void push(T t);
    T pop();
    T peek();

    bool isEmpty();
    int size();

    /* The doubly linked list used to implement the stack */
    DoublyLinkedList<T> *ll;
};

/* The GenStack implementation */

/* The default constructor*/
template <typename T>
GenStack<T>::GenStack(){
    ll = new DoublyLinkedList<T>();
    top = -1;
}

/* The destructor */
template <typename T>
GenStack<T>::~GenStack(){
    delete ll;
}

/* The method to push items onto the stack
* parameter t = the data value to push onto the stack
*/
template <typename T>
void GenStack<T>::push(T t){
    ll->insertFront(t);
    ++top;
}

/* The method to pop something off the stack
* return T = the data value that is popped off the stack
*/
template <typename T>
T GenStack<T>::pop(){
    if (isEmpty()){
        throw runtime_error("Stack is Empty");
    }
    --top;
    return ll->removeFront();
}

/* The method to peek something from the stack
* return T = the data value that on the top of the stack
*/
template <typename T>
T GenStack<T>::peek(){
    if (isEmpty()){
        throw runtime_error("Stack is Empty");
    }
    return ll->getFront();
}


/* The method to see if the stack is empty
* return bool
*   true = empty
*   false = not empty
*/
template <typename T>
bool GenStack<T>::isEmpty(){
    return top == -1;
}

/* The method to see the size of the stack
* return int = the size of the stack
*/
template <typename T>
int GenStack<T>::size(){
    return top+1;
}
#endif
