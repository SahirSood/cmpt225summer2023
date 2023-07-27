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

    //Function to calculate the height of a passed node
    int calheight(Node *p){
        //When both left and righ subtrees exists we return a height of the greater subtree + 1
        if(p->left && p->right){
            if (p->left->height < p->right->height)
                return p->right->height + 1;
            else return  p->left->height + 1;
        }

        //When either the left or the right subtree does not exist we return the height of the subtree that exits + 1
        else if(p->left && p->right == NULL){
            return p->left->height + 1;
        }
        else if(p->left ==NULL && p->right){
            return p->right->height + 1;
        }
        //Will never reach this return
        return 0;

        }

    //Function to calculate the neccicity of balancing
    //Balancing Function
    int bf(Node *n){
        //When both subtrees exits we return the diffrence in heights
        if(n->left && n->right){
            return n->left->height - n->right->height; 
        }
        //When either the left or the right subtree does not exist we return the height of the subtree that exit
        else if(n->left){
            return n->left->height; 
        }
        else if(n->right ){
            return -n->right->height;
        }
        //Will never reach this return
        return 0;
    }

    //Left Left Rotation
    //When a node is inserted at the left child of hte left subtree of the unbalanced node
    Node * llrotation(Node *n){
        Node *p;
        Node *tp;

        //set node equal to unbalced node
        p = n;
        //Node set to left subtree
        tp = p->left;
        //left subtree of unbalnced node is set to right subtree of tp
        p->left = tp->right;
        //right subtree of tp is set to old unbalnced node
        tp->right = p;

        return tp; 
    }

    //Right Right Rotation
    //When a node is inserted at the right child of hte right subtree of the unbalanced node
    Node * rrrotation(Node *n){
        Node *p;
        Node *tp;
        //set node equal to unbalced node
        p = n;
        //Node set to right subtree
        tp = p->right;
        //right subtree of unbalned node is set to left subtree of tp
        p->right = tp->left;
        //left subtree of tp is set to old  unbalanced node
        tp->left = p;

        return tp; 
    }

    //right left rotation
    // when a new node is inserted at the right child of the left subtree
    Node * rlrotation(Node *n){
        Node *p;
        Node *tp;
        Node *tp2;
        //set node equal to unbalced node
        p = n;
        //Node set to right subtree
        tp = p->right;
        //node set to left node of right subtree
        tp2 =p->right->left;
        //new right subtree of unbalanced node set to left subtree of 'bottom node'
        p -> right = tp2->left;
        //'middle node' left subtree set to right subtree of'bottom node'
        tp ->left = tp2->right;
        //tp2 becomes 'top node' with left subtree equal to old unbalanced node with new subtrees
        // and right subtree set to 'niddle node' with new subtrees
        tp2 ->left = p;
        tp2->right = tp; 
        
        return tp2; 
    }

    //Left Right Subtree
    //when a new node is inserted at the left child of the right subtree
    Node * lrrotation(Node *n){
        Node *p;
        Node *tp;
        Node *tp2;
        //set node equal to unbalced node
        p = n;
        //Node set to left subtree
        tp = p->left;
        //node set to right node of left subtree
        tp2 =p->left->right;
        //new left subtree of unbalanced node set to right subtree of 'bottom node'
        p -> left = tp2->right;
        //'middle node' right subtree set to left subtree of'bottom node'
        tp ->right = tp2->left;
        //tp2 becomes 'top node' with right subtree equal to old unbalanced node with new subtrees
        // and left subtree set to 'middle node' with new subtrees
        tp2 ->right = p;
        tp2->left = tp; 
        
        return tp2; 
    }

    //function that inserts a given value inthe avl tree
    //Recusrively
    Node* insert(Node *r,string data){
        //If the current node is null we create a new node
        //height set to 0 since it will be a leaf or root node
        //count set to 1 since it will be first instance of node in tree
        if(r==NULL){
            Node *n;
            n = new Node;
            n->word = data;
            r = n;
            r->left = r->right = NULL;
            r->height = 0; 
            r->count=1;
            return r;             
        }
        else{
            //Data is alphabetically smaller than the current node we know
            //According to BST properties it goes in the left subtree so we
            //Recursively call insert on left node
            if(data < r->word)
                r->left = insert(r->left,data);
            //If alphabetically greater we do the same on the right subtree
            else if(data>r->word)
                r->right = insert(r->right,data);
            //When Data is equal to current node we simply increment the count variable of the node
            else
                r->count++;

        }

        //Calculate the height of the added node
        r->height = calheight(r);


        //If node is left subtree heavy and the subtree is also left heavy
        //We call a Left Left Rotation
        if(bf(r)==2 && bf(r->left)==1){
            r = llrotation(r);
        }
        //If node is right subtree heavy and the subtree is also right heavy
        //We call a Right Right Rotation
        else if(bf(r)==-2 && bf(r->right)==-1){
            r = rrrotation(r);
        }
        //If node is right subtree heavy and the subtree is left heavy
        //We call a Right Left Rotation
        else if(bf(r)==-2 && bf(r->right)==1){
            r = rlrotation(r);
            
        }
        //If node is left subtree heavy and the subtree is also right heavy
        //We call a Left Right Rotation
        else if(bf(r)==2 && bf(r->left)==-1){
            r = lrrotation(r);
        }        

        return r;

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

    //Hekper functino that looks for the most frequent node updates the pointers
    //tracking the count and word of the most frequent
    void most_frequent_helper(string* word, int* max, Node* n)const{
        //Base Case
        if(n == nullptr){
            return;
        }
        //Calls itself on left subtree
        //(INORDER TRAVERSAL)
        most_frequent_helper(word, max, n->left);

        //Updates Varaibles if the count is greater than previously known
        //"most common" word

        if(n->count > *max){
            *word = n->word;
            *max = n->count;
        }
        //Calls itself on right subtree
        most_frequent_helper(word, max, n->right);
    }

    //Heler that returns the total number of nodes in the AVL tree
    int number_of_singletons_helper(Node* n)const{
        //Base Case
        if(n==nullptr){
            return 0;
        }
        //Returns The left and right subtree while adding 1 for each node visited
        if(n->count == 1){
            return 1 + number_of_singletons_helper(n->left) + number_of_singletons_helper(n->right);
        }
        //when count is greater than 1 we dont add 1 to the return value but call left and right subtree
        return number_of_singletons_helper(n->left) + number_of_singletons_helper(n->right);
    }

    //Prints the values of the nodes using inorder traversal
    void in_order_print(Node* n)const{
        //Base Case
        if(n==nullptr){
            return;
        }

        in_order_print(n->left);
        cout<<"{\""<<n->word<<"\", "<<n->count<<"}"<<endl;
        in_order_print(n->right);
    }

    //Checks if the AVL tree contains a given word
    bool lst_contains(Node*n, string x)const{
        //Base Case
        if(n==nullptr){
            return false;
        }
        //If we find the word we return true
        if(n->word == x){
            return true;
        }
        //When either the left or right subtree returns true then the bst has word
        if (lst_contains(n->left,x) || lst_contains(n->right,x))
        {
            return true;
        }
        return false;
    }

    public: 
        Wordlist(){} //default list constructor

        //Constructor that add all words from a file to our AVL tree
        Wordlist(string file_name){
            std::string word_;
            ifstream file_(file_name); //opens the file given in .cpp file  or terminal
            if(file_.is_open()){
                while(file_ >> word_){ // loops thorugh each word in file and saves to local variable
                    // cout<<word_<<endl;
                    add_word(word_);   // calls function that adds word to LL
                 }
                file_.close();
            }
            else{
                cerr << "Error opening file: " << file_name << endl;
            }
        }

        //destructor that empties the entire AVL tree when the code ends
        ~Wordlist(){
            deallocate(root);
        }

        //Function that gets total count of how many times a word appears in the list
        //count of node with the word as value
        int get_count(const string&w)const{
            Node* cur = root;
            while(cur!=nullptr){
                //when we find the node we return the count
                if(cur->word==w){
                    return cur->count;
                }
                //if word is less than our current node we know it will be in the left subtree
                else if (cur->word>w)
                {
                    cur = cur->left;
                }
                //if word is greater than our current node we know it will be in the right subtree
                else if(cur->word<w){
                    cur = cur->right;
                }
            }
            //Word not  found we return 0
            return 0;
        }

        
        //Returns the number of Unique words in the AVL tree
        int num_different_words()const{
            return totalNodes(root);
        }
        //Returns Total number of words(does not need to be unique)
        int total_words()const{
            return totalWords(root);
        }
        //Checks if the AVL tree has BST properties
        bool is_sorted()const{
            return is_sort_helper(root);
        }

        //returns a string of the word that appears most frequent and its count
        string most_frequent() const {
            string max_word;
            int max_count = 0;

            most_frequent_helper(&max_word, &max_count, root);

            // Check if any word was found and return the appropriate result
            if (max_count > 0) {
                string ret = max_word + " " + to_string(max_count);
                return ret;
            } else {
                return "No elements in the data structure.";
            }
        }


        //Returns number of words that appear only once
        int num_singletons()const{
            return number_of_singletons_helper(root);
        }

        //Function that adds a word to AVL tree
        void add_word(const string &w){
            root = insert(root,w);
        }

        //Prints the words in the AVL tree in alphabetical order
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
