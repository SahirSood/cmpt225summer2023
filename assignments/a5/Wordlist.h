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
    int calheight(Node* p){
        
        //When both left and right subtrees exist we return the maximum height between the two and add 1
        if(p->left && p->right){
            if(p->left->height<p->right->height){
                return p->right->height + 1;
            }
            else{
                return p->left->height +1;
            }
        }
        //When the left subtree exists but not the right, we return height of left subtree +1
        else if(p->left && p->right == nullptr){
            return p->left->height +1;
        }
        //When the right subtree exists but not the left, we return height of right subtree +1
        else if(p->right && p->left == nullptr){
           return p->right->height+1;
        }
        //if there is no left or right subtree then the height is 0
        return 0;
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
    
    Node* llrotation(Node* n){
        cout << "Performing LL rotation on: " << (n ? n->word : "nullptr") << endl;

        Node* p = n;
        Node* tp = p->left;

        p->left=tp->right;
        tp->right = p;
        return tp;
    }
    
    Node* rrrotation(Node*n){
        cout << "Performing LL rotation on: " << (n ? n->word : "nullptr") << endl;

        Node* p = n;
        Node* tp = p->right;

        p->right = tp->left;
        tp->left = p;
        return tp;              
    }

    Node* rlrotation(Node*n){
        cout << "Performing RL rotation on: " << (n ? n->word : "nullptr") << endl;

        Node* p = n;
        Node* tp = p->right;
        Node* tp2 = p->right->left;

        p -> right = tp2->left;
        tp ->left = tp2->right;
        tp2 ->left = p;
        tp2->right = tp; 
        return tp2;
    }

    Node* lrrotation(Node*n){
        cout << "Performing LR rotation on: " << (n ? n->word : "nullptr") << endl;

        Node* p = n;
        Node* tp = p->left;
        Node* tp2 = p->left->right;

        p -> left = tp2->right;
        tp ->right = tp2->left;
        tp2 ->right = p;
        tp2->left = tp; 
        return tp2;
    }

    Node* insert(Node*& cur, const string &w){
        if (cur == nullptr)
            {
                cur = new Node;
                cur->left = cur->right = nullptr;
                cur ->word = w;
                cur->height = cur->count = 0;
                return cur;
            }
        
        if(w < cur->word){
            cout << "Inserting: " << w << ", Current Node: " << (cur ? cur->word : "nullptr") << endl;

            cur->left = insert(cur->left,w);
        }

        else if(w>cur->word){
            cout << "Inserting: " << w << ", Current Node: " << (cur ? cur->word : "nullptr") << endl;

            cur->right = insert(cur->right,w);
        }
        else{
            cur->count++;
        }
    
        cout << "Height before updating: " << cur->height << endl;
        cur->height = calheight(cur);
        cout << "Height after updating: " << cur->height << endl;


        // if(bf(cur)==2 && bf(cur->left)==1){
        //     cur = llrotation(cur);
        // }
        // else if(bf(cur)==-2 && bf(cur->right)==-1){
        //     cur = rrrotation(cur);
        // }
        // else if(bf(cur)==-2 && bf(cur->right)==1){
        //     cur = rlrotation(cur);
        // }
        // else if(bf(cur)==2 && bf(cur->left)==-1){
        //     cur = lrrotation(cur);
        // }        
        return cur;

        }

    int totalNodes(Node* n)const{
        if(n == nullptr){
            return 0;
        }
        return 1 + totalNodes(n->left) + totalNodes(n->right);
    }
    int totalWords(Node* n)const{
        if(n == nullptr){
            return 0;
        }
        return n->count + totalNodes(n->left) + totalNodes(n->right);
    }
    void deallocate(Node* cur){
        if(cur == nullptr){
            return;
        }

        deallocate(cur->left);
        deallocate(cur->right);
        delete cur;
    }
    bool is_sort_helper(Node* n)const{
        if(n == nullptr){
            return true;
        }
        if(n->left->word > n->word || n->right->word < n->word){
            return false;
        }

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

    public: 
        Wordlist(){} //default list constructor

        Wordlist(string file_name){
            
            std::string word_;
            ifstream file_(file_name); //opens the file given in .cpp file  or terminal
            int count = 0;
            if(file_.is_open()){
                while(file_ >> word_){ // loops thorugh each word in file and saves to local variable
                    cout<<"Word: "<<word_<<endl;
                    add_word(word_);   // calls function that adds word to LL
                    count++;
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
