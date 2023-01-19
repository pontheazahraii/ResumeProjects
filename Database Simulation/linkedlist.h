#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <exception>
// #include "listADT.h"
using namespace std;

/* List Node Class */
template <typename T>
class ListNode{
    public:
    ListNode();
    ListNode(T d);
    ~ListNode();

    /* The pointer to the next node in the list */
    ListNode<T> *next;

    /* The pointer to the previous node in the list */
    ListNode<T> *prev;

    /* The data value of the node */
    T data;
};

/* List Node Implementation */

/* The default constructor */
template <typename T>
ListNode<T>::ListNode(){}

/* The overloaded constructor
* parameter d = the data value of the list node
*/
template <typename T>
ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}

/* The destructor */
template <typename T>
ListNode<T>::~ListNode(){
    delete next;
    delete prev;
}

//-----------------------------------------

/* Doubly Linked List Class */
template <typename T>
class DoublyLinkedList {
    private:
    /* The front node in the list */
    ListNode<T> *front;

    /* The back node in the list */
    ListNode<T> *back;

    /* The size of the list */
    unsigned int size;

    public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertFront(T d);
    void insertBack(T d);

    T removeFront();
    T removeBack();
    T removeNode(T v);

    int find(T v);
    bool isEmpty();

    unsigned int getSize();
    T getFront();
};

/* Doubly Linked List Implementation */

/* the default constructor */
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(){
    front = NULL;
    back = NULL;
    size = 0;
}

/* The destructor */
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
    ListNode<T> *node = front;
    ListNode<T> *nodeToDelete = front;

    //iterate through the list and delete each node
    while (node != NULL){
        nodeToDelete = node->next;
        delete node;
        node = nodeToDelete;
    }
}

/* the method to insert to the front of the list
* parameter d = the data point to insert to the front the list
*/
template <typename T>
void DoublyLinkedList<T>::insertFront(T d){
    ListNode<T> *node = new ListNode<T>(d);

    if (isEmpty()){ //check if empty
        back = node;
    } else { //if not empty
        node->next = front;
        front->prev = node;
    }
    front = node;
    ++size; 
}

/* the method to insert to the back of the list
* parameter d = the data point to insert to the back of the list
*/
template <typename T>
void DoublyLinkedList<T>::insertBack(T d){
    ListNode<T> *node = new ListNode<T>(d);
    if (isEmpty()){ //if empty
        front = node;
    } else { //if not empty
        node->prev = back;
        back->next = node;
    }
    back = node;
    ++size;
}

/* the method to remove an element from the front of the list
* return T = the data value removed from the front of the list
*/
template <typename T>
T DoublyLinkedList<T>::removeFront(){
    if (isEmpty()){ //if empty
        throw runtime_error("List is Empty");
    }

    ListNode<T> *temp = front;

    if (front->next == NULL){ //if only one node
        back = NULL;
    } else { //if more than one node
        front->next->prev = NULL;
    }

    front = front->next;
    temp->next = NULL;
    T data = temp->data;
    --size;
    delete temp;
    return data;
}

/* the method to remove an element from the back of the list
* return T = the data value removed from the back of the list
*/
template <typename T>
T DoublyLinkedList<T>::removeBack(){
    if (isEmpty()){ //if empty
        throw runtime_error("List is Empty");
    }

    ListNode<T> *temp = front;

    if (back->prev == NULL){ //if only one node
        front = NULL;
    } else { //if more than one node
        back->prev->next = NULL;
    }

    back = back->prev;
    temp->prev = NULL;
    T data = temp->data;
    --size;
    delete temp;
    return data;
}

/* the method to remove an element from  the list
* return T = the data value removed from the list
*/
template <typename T>
T DoublyLinkedList<T>::removeNode(T v){
    if (isEmpty()){ //if empty
        throw runtime_error("List is Empty");
    }

    ListNode<T> *curr = front;

    //while the current data point is not the value we are looking to delete
    while(!(curr->data == v)){
        curr = curr->next;

        //if the value does not exist
        if (curr == NULL){
            throw runtime_error("Value does not exist");
        }
    }

    //if in the middle of the list
    if (curr != front && curr != back){
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    //if in the front of the list
    if (curr == front){
        front = curr->next;
        front->prev = NULL;
    }

    //if in the back of the list
    if (curr == back){
        back = curr->prev;
        back->next = NULL;
    }

    curr->next = NULL;
    curr->prev = NULL;
    T data = curr->data;
    --size;
    delete curr;
    return data;
}

/* the method to find the position of a value in the list
* parameter v = the value to find
* return int = the position of the value
*/
template <typename T>
int DoublyLinkedList<T>::find(T v){
    int pos = -1;
    ListNode<T> *curr = front;

    //while the value is not found
    while (curr != NULL){
        ++pos;

        //if the value is found
        if (curr->data.isEqual(v)){
            break;
        }
        curr = curr->next;
    }

    //if the value was not found
    if (curr == NULL){
        pos = -1;
    }

    return pos;
}

/* the method to see if the list is empty
* return bool
*   true = empty
*   false = not empty
*/
template <typename T>
bool DoublyLinkedList<T>::isEmpty(){
    return size == 0;
}

/* the method to return the size of the list
* return unsigned int = the number of elements in the list
*/
template <typename T>
unsigned int DoublyLinkedList<T>::getSize(){
    return size;
}

/* the method to get the front value on the list
* return T = the value of the front of the list
*/
template <typename T>
T DoublyLinkedList<T>::getFront(){
    return front->data;
}
#endif
