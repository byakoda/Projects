#ifndef DSWTREE_H
#define DSWTREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class DSWTree {
public: // DO NOT CHANGE THIS PART.
    DSWTree();

    DSWTree(const DSWTree<T> &obj);

    ~DSWTree();

    bool isEmpty() const;

    int getHeight() const;
    
    const int getNodeHeight(const T& element) const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    DSWTree<T> &operator=(const DSWTree<T> &rhs);

    bool isBalanced();

    void balance();

    void createBackbone(Node<T> *&root);

    void createCompleteTree(Node<T> *&root, int size);

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

    void leftrotation(Node<T> *&root, int number){
        Node<T> *current = root;
        Node<T> *save = NULL;
        while(number > 0 && current != NULL){
            if(current->right){
                Node<T> *right_child = current->right;
                
                current->right = right_child->left;
                right_child->left = current;
    
                if(save == NULL){
                    root = right_child;
                }
                
                else{
                    save->right = right_child;
                }
    
                save = right_child;
                current = right_child->right;
            } else {
                save = current;
                current = current->right;
            }
            --number;
        }
    }

    bool helper_isBalanced(Node<T>* r){
        if(r == NULL){
            return true;
        }
        
        int left_height, right_height;
        
        if(r -> left != NULL){
            left_height = r -> left -> height;
        }
        
        else{
            left_height = -1;
        }

        if(r -> right != NULL){
            right_height = r -> right -> height;
        }
        
        else{
            right_height = -1;
        }
        
        if(abs(right_height - left_height) > 1){
            return false;
        }

        return helper_isBalanced(r -> right) && helper_isBalanced(r -> left);
    }


    Node<T>* helper_copycons(const Node<T>* r){
        
        if(r == NULL){
            return NULL;
        }
        
        Node<T>* new_node = new Node<T>(r -> element, NULL, NULL, r -> height);
        
        new_node -> left = helper_copycons(r -> left);
        new_node -> right = helper_copycons(r -> right);
        
        return new_node;
    }

    bool helper_remove(Node<T>* &r , const T &element) {
        if(r == NULL){
            return false;
        }
        
        else if( r-> element > element){
            helper_remove(r-> left, element);
        }
        
        else if( r-> element < element){
            helper_remove(r-> right, element);
        }
        
        else{
            if(r->right != NULL && r -> left != NULL){
                r -> element = helper_getMin(r -> right);
                helper_remove(r->right, r -> element);
            }
            
            else{
                Node<T>* to_delete = r; 
                r = (r -> left != NULL)? r -> left: r -> right;
                delete to_delete;
                return true;
            }
        }
    }

    const int helper_getNodeHeight(Node<T>* r, const T& element) const {
        if(r == NULL){
            return -1;
        }
        
        if(element == r -> element){
            return r -> height;
        }
        
        if(element < r -> element){
            return helper_getNodeHeight(r -> left, element);
        }
        
        return helper_getNodeHeight(r -> right, element);
    }

    const T &helper_get(Node<T>* r,const T& element) const {
        
        if(r == NULL){
            throw NoSuchItemException();
        }
        
        if(element == r -> element){
            return r -> element;
        }
        
        if(element < r -> element){
            return helper_get(r -> left, element);
        }
        
        return helper_get(r -> right, element);
        
    }

    const T &helper_getNext(Node<T>* r, const T &element) const{

        if(r == NULL){
            throw NoSuchItemException();
        }
        
        T var = helper_getMax(r);
        
        if(var < element || var == element){
            throw NoSuchItemException();
        }
        
        if(element == r -> element){
            return helper_getMin(r -> right);
        }
        
        if(element > r -> element){
            if(r -> right != NULL){
                return helper_getNext(r -> right, element);
            }
        }
        
        if(element < r -> element){
            if(r -> left != NULL){
                if(helper_getMax(r -> left) < element || helper_getMax(r -> left) == element){
                    return r -> element;
                }
                return helper_getNext(r -> left, element);
            }
            return r -> element;
        }
    }

    const T &helper_getCeiling(Node<T>* r, const T &element) const{

        if(r == NULL){
            throw NoSuchItemException();
        }
        
        T var = helper_getMax(r);
        
        if(var < element){
            throw NoSuchItemException();
        }
        
        
        if(element == r -> element){
            return r -> element;
        }
        
        if(element > r -> element){
            if(r -> right != NULL){
                return helper_getCeiling(r -> right, element);
            }
        }
        
        if(element < r -> element){
            if(r -> left != NULL){
                if(helper_getMax(r -> left) < element){
                    return r -> element;
                }
                return helper_getCeiling(r -> left, element);
            }
            return r -> element;
        }
    }
    
    const T &helper_getFloor(Node<T>* r, const T &element) const{

        if(r == NULL){
            throw NoSuchItemException();
        }
        
        T var = helper_getMin(r);
        
        if(var > element){
            throw NoSuchItemException();
        }
        
        
        if(element == r -> element){
            return r -> element;
        }
        
        if(element > r -> element){
            if(r -> right != NULL){
                if(helper_getMin(r -> right) > element){
                    return r -> element;
                }
                return helper_getFloor(r -> right, element);
            }
            return r -> element;
        
        }
        
        if(element < r -> element){
            if(r -> left != NULL){
                return helper_getFloor(r -> left, element);
            }
        }
    }


    const T &helper_getMin(const Node<T>* r) const{
        if(r == NULL){
            throw NoSuchItemException();
        }
        
        if(r -> left == NULL){
            return r -> element;
        }
        
        return helper_getMin(r -> left);
    }


    const T &helper_getMax(const Node<T>* r) const{
        if(r == NULL){
            throw NoSuchItemException();
        }
        
        if(r -> right == NULL){
            return r -> element;
        }
        
        return helper_getMax(r -> right);
    }

    void delete_tree(Node<T>* r){
        if(r == NULL){
            return;
        }
        
        delete_tree(r -> left);
        delete_tree(r -> right);
        delete r;
    }
    
    
    Node<T>* helper_insert(Node<T>*& r,const T &element) const{
        if(r == NULL){
            Node<T>* new_node = new Node<T>(element, NULL, NULL, 0);
            r = new_node;
            return r;
        }

        if(element > r -> element){
            r -> right = helper_insert(r -> right, element);
        }

        else if(element < r -> element){
            r -> left = helper_insert(r-> left, element);
        }
        
        return r;
    }
    
    
    int helper_size(const Node<T>* r) const{
        if( r == NULL){
            return 0;
        }
        
        return 1 + helper_size(r -> left) + helper_size(r -> right);
    }
    
    
    
    int maximum(int a, int b) const{
        if(a < b){
            return b;
        }
        
        return a;
    }
    

    void height_seter(Node<T>* r) const{
        if(r){
            r -> height = helper_height(r);
            
            height_seter(r -> left);
            height_seter(r -> right);
        }
        
        return;
    }
    
    int helper_height(Node<T>* r) const{
        if(r == NULL){
            return -1;
        }
        
        int left_side = helper_height(r -> left);
        int right_side = helper_height(r -> right);
        return 1 + maximum(left_side, right_side);
    }

    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;

private: // DO NOT CHANGE THIS PART.
    Node<T> *root;
};

template<class T>
DSWTree<T>::DSWTree() {
     
    root = NULL;
}

template<class T>
DSWTree<T>::DSWTree(const DSWTree<T> &obj){
     
    root = helper_copycons(obj.root);
}

template<class T>
DSWTree<T>::~DSWTree() {
     
    delete_tree(root);
    root = NULL;
}

template<class T>
bool DSWTree<T>::isEmpty() const {
     
    if(root == NULL){
        return true;
    }

    return false;
}

template<class T>
int DSWTree<T>::getHeight() const {
    return helper_height(root);
}

template<class T>
int DSWTree<T>::getSize() const {
    return helper_size(root);
}

template<class T>
bool DSWTree<T>::insert(const T &element) {
     
    if(helper_insert(root, element)){
        height_seter(root);
        return true;
    }

    return false;
}

template<class T>
bool DSWTree<T>::remove(const T &element) {
     
    if(helper_remove(root, element)){
        height_seter(root);
        return true;
    }
    
    return false;
}

template<class T>
void DSWTree<T>::removeAllNodes() {
     
    delete_tree(root);
    root = NULL;
}

template<class T>
const T &DSWTree<T>::get(const T &element) const {
     
    return helper_get(root, element);
}

template<class T>
void DSWTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        /*TODO*/
        if (isEmpty()) {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }


        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } 
    
    else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } 
    else if (tp == postorder) {
         
        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }


        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
void DSWTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
         
        if (node == NULL)
            return;
            
        std::cout << "\t" << node->element;

        if (node->left) {
            std::cout << "," << std::endl;
        }
        
        print(node->left, preorder);


        if (node->right) {
            std::cout << "," << std::endl;
        }
        
        print(node->right, preorder);
    }
    else if (tp == inorder) {
        
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        
        print(node->right, inorder);
    }
    else if (tp == postorder) {
         
        if (node == NULL)
            return;

        print(node->left, postorder);
        
        print(node->right, postorder);
        
        std::cout << "\t" << node->element;
        
        if(node != root){
            std::cout << "," << std::endl;
        }
    }
}

template<class T>
void DSWTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void DSWTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
DSWTree<T> &DSWTree<T>::operator=(const DSWTree<T> &rhs) {
     
    if(this == &rhs){
        return *this;
    }
    
    delete_tree(root);

    root = helper_copycons(rhs.root);
    
    return *this;
}

template <class T>
void DSWTree<T>::balance() {
     
    createBackbone(root);
    createCompleteTree(root, helper_size(root));
}

template <class T>
bool DSWTree<T>::isBalanced() {
     
    return helper_isBalanced(root);
}

template <class T>
void DSWTree<T>::createBackbone(Node<T> *&root) {
     
    Node<T>* temp = root;
    Node<T>* prev = NULL;
    while(temp != NULL){
        if(temp -> left){
            Node<T>* left_child = temp -> left;
            temp -> left = left_child -> right;
            left_child -> right = temp;
            if(prev == NULL){
                root = left_child;
            }
            if(prev != NULL){
                prev -> right = left_child;
            }
            temp = left_child;
        }
        else{    
            prev = temp;
            temp = temp -> right;
        }
    }
    height_seter(root);
}


template <class T>
void DSWTree<T>::createCompleteTree(Node<T> *&root, int n) {
    int m = pow(2, floor(log2(n + 1))) - 1;
    leftrotation(root, n - m);
    
    while (m > 1) {
        m /= 2;
        leftrotation(root, m);
    }
    
    height_seter(root);
}


template<class T>
const T &DSWTree<T>::getCeiling(const T &element) const {
     
    return helper_getCeiling(root, element);
}

template<class T>
const T &DSWTree<T>::getFloor(const T &element) const {
     
    return helper_getFloor(root, element);
}

template<class T>
const T &DSWTree<T>::getMin() const {
     
    return helper_getMin(root);
}

template<class T>
const T &DSWTree<T>::getMax() const {
     
    return helper_getMax(root);
}

template<class T>
const T &DSWTree<T>::getNext(const T &element) const {
     
    return helper_getNext(root, element);
}

template<class T>
const int DSWTree<T>:: getNodeHeight(const T& element) const {
     
    return helper_getNodeHeight(root, element);
}

#endif //DSWTREE_H
