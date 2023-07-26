// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Sahir Sood>
// St.# : <301462135>
// Email: <ssa434@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//
// IMPORTANT: no global variables are permitted in this file!
//
// It is okay to define helper functions defined outside the class.
//

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement an AVL tree for the word list. You can *add*
    // extra variables/methods/features to this struct if you like, but you must
    // keep its name the same, and also keep the word, count, left, and right
    // variables as defined.
    //
    struct Node
    {
        string word;
        int count;
        Node *left;
        Node *right;

        int height;
    };

    Node *root = nullptr;

    //Helper Function that returns the height of a given node
    int height(Node* t)
    {
        return (t == NULL ? -1 : t->height);
    }
    
    //Balancing Functions
    //Calculates the difference in heights of subtrees to see if BST is balanced
    //returns value of left subtree height - right subtree height to find difference
    int bf(Node* p){
        //Returns differnce if there is 2 subtees
        if(p->left && p->right){
            return p->left->height - p->right->height;
        }
        //When both subtrees not avaialable returns the height of the tree that is available
        else if(p->right && p->left == nullptr){
            return p->right->height;
        }
        else if(p->left && p->right == nullptr){
            return p->left->height;
        }
        return 0;
    }

    // Right-Right Rotation
    // This function performs a rotation to balance the tree when the right subtree
    // of a node becomes taller than its left subtree. 
    Node* rrrotation(Node* &t)
    {
        // Store the left child of the original node t in a variable u
        Node* u = t->left;
        
        // Move the right child of u to be the left child of t
        t->left = u->right;

        // Perform the rotation by making u the new root of the subtree
        u->right = t;

        // Update the heights of t and u
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(u->left), t->height) + 1;
        
        // Return the new root of the subtree u
        return u;
    }

    // Left-Left Rotation
    // This function performs a rotation to balance the tree when the left subtree
    // of a node becomes taller than its right subtree. 
    Node* llrotation(Node* &t)
    {
        // Store the right child of the original node t in a variable u
        Node* u = t->right;

        // Move the left child of u to be the right child of t
        t->right = u->left;

        // Perform the rotation by making u the new root of the subtree
        u->left = t;

        // Update the heights of t and u
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        
        // Return the new root of the subtree u
        return u;
    }

    // Left-Right-Left Rotation
    // This function performs two rotations to balance the tree when a node's left subtree
    // is taller than its right subtree, and the left child's right subtree is taller than
    // its left subtree. 
    Node* lrlrotation(Node* &t)
    {
        // Perform a Right-Right rotation on the right subtree of the original node t
        t->right = rrrotation(t->right);

        // Perform a Left-Left rotation on the original node t
        return llrotation(t);
    }

    // Right-Left-Right Rotation
    // This function performs two rotations to balance the tree when a node's right subtree
    // is taller than its left subtree, and the right child's left subtree is taller than
    // its right subtree. 
    Node* rlrrotation(Node* &t)
    {
        // Perform a Left-Left rotation on the left subtree of the original node t
        t->left = llrotation(t->left);

        // Perform a Right-Right rotation on the original node t
        return rrrotation(t);
    }


        // Inserts a given string into the AVL tree
    // The function first adds the word to the binary search tree (BST) normally, following
    // the properties of a BST. Then it balances the tree to ensure it maintains the AVL
    Node* insert(Node* t, string x)
    {
        // Base Case
        // If we reach a node (null), we create a new node with the value x and update
        // its height to 0 (since it will be a leaf node). 'count' is also set to 1 since
        // it is a unique value in the tree.
        if (t == NULL)
        {
            t = new Node;
            t->word = x;
            t->height = 0;
            t->left = t->right = NULL;
            t->count = 1;
        }

        // If the node is not null, we look for the appropriate place to insert the new node.
        // Based on the properties of a BST:
        else if (x < t->word)
        {
            t->left = insert(t->left, x);
            
            // After inserting the new node, we check if a rotation needs to be done to balance the tree.
            // The 'bf' function (which calculates the balance factor) is used to check if the AVL property is violated
            //height differences must be less than 2

            if (bf(t) == 2)
            {
                // If the newly inserted value is in the left subtree of the current node, we perform a
                // Right-Right rotation (rrrotation) on the current node.
                if (x < t->left->word)
                    t = rrrotation(t);
                // Otherwise, we perform a Right-Left-Right rotation (rlrrotation) on the current node.
                else
                    t = rlrrotation(t);
            }
        }
        else if (x > t->word)
        {
            t->right = insert(t->right, x);

            // After inserting the new node, we check if a rotation needs to be done to balance the tree.
            // The 'bf' function is used to check if the AVL property is violated at this node (bf(t) == 2
            // indicates the right subtree is taller by more than 1).
            if (bf(t) == 2)
            {
                // If the newly inserted value is in the right subtree of the current node, we perform a
                // Left-Left rotation (llrotation) on the current node.
                if (x > t->right->word)
                    t = llrotation(t);
                // Otherwise, we perform a Left-Right-Left rotation (lrlrotation) on the current node.
                else
                    t = lrlrotation(t);
            }
        }
        else
        {
            // If the value already exists in the tree we increment count variable.
            t->count++;
        }

        // Update the height of the current node based on the heights of its left and right subtrees.
        // Then, return the updated node.
        t->height = max(height(t->left), height(t->right)) + 1;
        return t;
    }

    //Returns total number of nodes in a BST or AVL tree
    int totalNodes(Node* n)const{
        //null reached meaning no node, return 0
        if(n == nullptr){
            return 0;
        }
        //non null node, we add 1 and call left and right subtrees.
        return 1 + totalNodes(n->left) + totalNodes(n->right);
    }
    //Returnns total words in a BST or AVL tree
    //A node in a tree may contain multiple words
    //ie Node has word hello, but count 3 times.
    //So hello 3 times
    int totalWords(Node* n)const{
        if(n == nullptr){
            return 0;
        }
        //if node is non null we add the count of the node and call left and right subtrees.
        return n->count + totalWords(n->left) + totalWords(n->right);
    }

    //Function that deletes every node in a tree
    void deallocate(Node* cur){
        //Base case
        if(cur == nullptr){
            return;
        }
        //Call left and right subtrees
        deallocate(cur->left);
        deallocate(cur->right);
        //when all nodes are called we delete the nodes
        delete cur;
    }

    //Helper function to see if a tree is sorted

    bool is_sort_helper(Node* n) const {
        // Base case, if we reach the end of a tree (nullptr), return true
        if (n == nullptr) {
            return true;
        }

        // Check if the left child exists and its word is greater than the current node's word
        if (n->left != nullptr && n->left->word > n->word) {
            return false;
        }

        // Check if the right child exists and its word is less than the current node's word
        if (n->right != nullptr && n->right->word < n->word) {
            return false;
        }

        // Recursively check the left and right subtrees
        return is_sort_helper(n->left) && is_sort_helper(n->right);
    }

    
    void most_frequent_helper(string* word, int* max, Node* n)const{
        if(n == nullptr){
            return;
        }
        most_frequent_helper(word, max, n->left);

        if(n->count > *max){
            *word = n->word;
            *max = n->count;
        }

        most_frequent_helper(word, max, n->right);
    }

    int number_of_singletons_helper(Node* n)const{
        if(n==nullptr){
            return 0;
        }
        if(n->count == 1){
            return 1 + number_of_singletons_helper(n->left) + number_of_singletons_helper(n->right);
        }
        return number_of_singletons_helper(n->left) + number_of_singletons_helper(n->right);
    }

    void in_order_print(Node* n)const{
        if(n==nullptr){
            return;
        }

        in_order_print(n->left);
        cout<<"{\""<<n->word<<"\", "<<n->count<<"}"<<endl;
        in_order_print(n->right);
    }

    bool lst_contains(Node*n, string x)const{
        if(n==nullptr){
            return false;
        }
        if(n->word == x){
            return true;
        }
        if (n->left || n->right)
        {
            return true;
        }
        return false;
        

    }

    public: 
        Wordlist(){} //default list constructor

        Wordlist(string file_name){
            
            std::string word_;
            ifstream file_(file_name); //opens the file given in .cpp file  or terminal
            if(file_.is_open()){
                while(file_ >> word_){ // loops thorugh each word in file and saves to local variable
                    add_word(word_);   // calls function that adds word to LL
                 }
                file_.close();
            }
            else{
                cerr << "Error opening file: " << file_name << endl;
            }
        }


        ~Wordlist(){
            deallocate(root);
        }

        int get_count(const string&w)const{
            Node* cur = root;
            while(cur!=nullptr){
                if(cur->word==w){
                    return cur->count;
                }
                else if (cur->word>w)
                {
                    cur = cur->left;
                }
                else if(cur->word<w){
                    cur = cur->right;
                }
            }
            return 0;
        }

        

        int num_different_words()const{
            return totalNodes(root);
        }

        int total_words()const{
            return totalWords(root);
        }

        bool is_sorted()const{
            return is_sort_helper(root);
        }

        string most_frequent()const{
            string max;
            int max_num;
            
            most_frequent_helper(&max,&max_num,root);

            return max;
        }

        int num_singletons()const{
            return number_of_singletons_helper(root);
        }

        void add_word(const string &w){
            root = insert(root,w);
        }

        void print_words()const{
            in_order_print(root);
        }

    
    //
    // IMPORTANT: root is the only variable that can be defined in this class.
    // It should point to the top node of your AVL tree. When root == nullptr,
    // the tree is empty.
    //
    // No variables other than root are permitted!
    //


}; // class Wordlist

//
// Make sure to thoroughly test your code as you go!
//
