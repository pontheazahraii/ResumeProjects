#ifndef BST_H
#define BST_H
#include <iostream>

using namespace std;

template <class T>
class TreeNode{
    public:
        TreeNode();
        TreeNode(T key);
        virtual ~TreeNode();

        /* The data */
        T key;

        /* Left pointer */
        TreeNode<T> *left;

        /* Right pointer */
        TreeNode<T> *right;
};

/* The default constructor */
template <class T>
TreeNode<T>::TreeNode(){
    left = NULL;
    right = NULL;
    key = NULL;
}

/* The overloaded constructor */
template <class T>
TreeNode<T>::TreeNode(T k){
    left = NULL;
    right = NULL;
    key = k;
}

/* The destructor */
template <class T>
TreeNode<T>::~TreeNode(){
    left = NULL;
    right = NULL;
}

//---------------------------------------------

template <class T>
class BST{
    public:
        BST();
        virtual ~BST();
        void insert(T value);
        void insert(TreeNode<T> *node);
        bool contains(T value);//search
        T find(T value);
        bool deleteNode(T k);
        bool isEmpty();

        T* getMin();
        T* getMax();
        TreeNode<T> *getSuccessor(TreeNode<T> *d); //d represents the node we are going to delete
        void printNodes();
        void recPrint(TreeNode<T> *node);
        void inOrder(TreeNode<T> *node);
        T calcSum(TreeNode<T> *node);
        TreeNode<T>* getRoot();
        void RSerialization(string f);
        int getSize();
    private:
        /* The root of the tree */
        TreeNode<T> *root;

        /* The size of the tree */
        int size;
};

/* The default constructor */
template <class T>
BST<T>::BST(){
    root = NULL;
    size = 0;
}

/* The destructor */
template <class T>
BST<T>::~BST(){
    delete root;
    //build some character
    //and do a little research
}

/* the root accessor
* return = the root node
*/
template <class T>
TreeNode<T>* BST<T>::getRoot(){
    return root;
}

/* The preorder print method
* parameter node = the starting node to print
*/
template <class T>
void BST<T>::recPrint(TreeNode<T> *node){
    if(node == NULL)
        return;

    cout << node->key << endl;
    recPrint(node->left);
    recPrint(node->right);
}

/* The inorder print method
* parameter node = the starting node to print
*/
template <class T>
void BST<T>::inOrder(TreeNode<T> *node) {
    if (node != NULL) {
        inOrder(node->left);
        cout << node->key << endl;
        inOrder(node->right);
    }
}

/* The method to calculate the sum of the nodes
* parameter node = the starting node to calculate from
*/
template <class T>
T BST<T>::calcSum(TreeNode<T> *node){
    if(node == NULL)
        return 0;

    return (node->key + calcSum(node->left) + calcSum(node->right));
}

/* The method to print all the nodes in the tree*/
template <class T>
void BST<T>::printNodes(){
    recPrint(root);
}

/* The is Empty method
* return = if the BST is empty
*/
template <class T>
bool BST<T>::isEmpty(){
    return (size == 0);
}

/* The minimum value of the tree
* return = the minimum value of the tree
*/
template <class T>
T* BST<T>::getMin(){
    if(isEmpty())
        return NULL;

    TreeNode<T> *current = root;
    while(current->left != NULL){
        current = current->left;
    }
    return &(current->key);
}

/* The maximum value of the tree
* return = the maximum value of the tree
*/
template <class T>
T* BST<T>::getMax(){
    if(isEmpty())
        return NULL;

    TreeNode<T> *current = root;
    while(current->right != NULL){
        current = current->right;
    }
    return &(current->key);
}

/* The insert method
* parameter value = the value to insert
*/
template <class T>
void BST<T>::insert(T value){
    TreeNode<T> *node = new TreeNode<T>(value);

    if(isEmpty()) {
        root = node;
    } else {
        //the tree is not empty
        TreeNode<T> *current = root;
        TreeNode<T> *parent = NULL;

        while(true) {
            parent = current;

            if(value < current->key){
                //we go left
                current = current->left;
                if(current == NULL){
                    //we found the insertion point
                    parent->left = node;
                    break;
                }
            } else {
                //we go right
                current = current->right;
                if(current == NULL){
                    //we found the insertion point
                    parent->right = node;
                    break;
                }
            }
        }
    }
    ++size;
}

/* The insert method
* parameter node = the node to insert
*/
template <class T>
void BST<T>::insert(TreeNode<T> *node){
    if(isEmpty()) {
        root = node;
    } else {
        //the tree is not empty
        TreeNode<T> *current = root;
        TreeNode<T> *parent = NULL;

        while(true) {
            parent = current;

            if(node->key < current->key){
                //we go left
                current = current->left;
                if(current == NULL){
                    //we found the insertion point
                    parent->left = node;
                    break;
                }
            } else {
                //we go right
                current = current->right;
                if(current == NULL){
                    //we found the insertion point
                    parent->right = node;
                    break;
                }
            }
        }
    }
    ++size;
}

/* The contains method
* parameter value = the value to check
* return = if it contains the value
*/
template <class T>
bool BST<T>::contains(T value){
    if(isEmpty())
        return false;

    TreeNode<T> *current = root;

    while(current->key != value){
        if(value < current->key)
            current = current->left;
        else
            current = current->right;

        if(current == NULL)
            return false;
    }
    return true;
}

/* The find method
* parameter value = the value to find
* return = the value
*/
template <class T>
T BST<T>::find(T value){
    TreeNode<T> *curr = NULL;
    if(isEmpty())
        return curr->key;

    TreeNode<T> *current = root;

    while(current->key != value){
        if(value < current->key)
            current = current->left;
        else
            current = current->right;

        if(current == NULL)
            return curr->key;
    }
    delete curr;
    return current->key;
}

/* The method to delete a node
* parameter k = the value to delete
* return = if the node is deleted
*/
template <class T>
bool BST<T>::deleteNode(T k){
    //tree is empty
    if (isEmpty()){
        return false;
    }

    TreeNode<T> *curr = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;

    //does the key exist - contains method
    //can also use the contains method
    while (curr->key != k){
        parent = curr;
        if (k < curr->key){
            isLeft = true;
            curr = curr->left;
        } else {
            isLeft = false;
            curr = curr->right;
        }
        if(curr == NULL){
            return false;
        }
    }

    if(curr->left == NULL && curr->right == NULL){
        //node has 0 children
        if(curr == root){
            root = NULL;
        } else if (isLeft){
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    } else if (curr->right == NULL){
        //node has 1 child -> left child
        if (curr == root){
            root = curr->left;
        } else if (isLeft){
            parent->left = curr->left;
        } else {
            parent->right = curr->left;
        }
    } else if (curr->left == NULL){
        //node has 1 child -> right child
        if (curr == root){
            root = curr->right;
        } else if (isLeft){
            parent->left = curr->right;
        } else {
            parent->right = curr->right;
        }
    } else {
        //node has 2 children
        //at this point we begin to cry and take a 4 hr nap
        TreeNode<T> *succ = getSuccessor(curr);
        if (curr == root){
            root = succ;
        } else if (isLeft){
            parent->left = succ;
        } else {
            parent->right = succ;
        }
        succ->left = curr->left;
    }

    curr->left = NULL;
    curr->right = NULL;
    delete curr;
    size--;
    return true;
}

/* The method to return the successor
* parameter d = the node to find the successor of
* return = the successor of the node
*/
template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){
    TreeNode<T> *succ_parent = d;
    TreeNode<T> *succ = d;
    TreeNode<T> *curr; d->right;

    //find the successsor
    while (curr != NULL){
        succ_parent = succ;
        succ = curr;
        curr = curr->left;
    }

    //check if the succ is a descendent of d->right or if it is d->right
    if (succ != d->right){
        succ_parent->left = succ->right;
        succ->right = d->right;
    }

    return succ;
}

//serialization of a tree node
template <class T>
void BST<T>::RSerialization(string f){
    ofstream output;
    output.open(f);

    if(root == NULL){
        cout << "ERROR: BST is empty. Please try again" << endl;
    }

    else{
        output << root->data->getInfoS() << endl;
    }
    if(root->left != NULL){
        TSerialization(root->left, f);
    }
    if(root->right != NULL){
        TSerialization(root->right, f);
    }
}
template <class T>
int BST<T>::getSize(){
    return size;
}

#endif
