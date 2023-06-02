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

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement the singly-linked list for the word list. You
    // can *add* extra variables/methods/features to this struct if you like,
    // but you must keep its name the same, and also keep the word, count, and
    // next variables as defined.
    //
    struct Node
    {
        string word;
        int count;
        Node *next;
    };

    Node* head = nullptr;


    public:

        Wordlist(){} // default list constructor

        Wordlist (string file_name){
            
            std::string word_;
            ifstream file_(file_name); //opens the file given in .cpp file  or terminal
            if(file_.is_open())
            {
                while(file_ >> word_){ // loops thorugh each word in file and saves to local variable
                    add_word(word_);   // calls function that adds word to LL
                 }
                file_.close();
            }
            else{
                cerr << "Error opening file: " << file_name << endl;
            }
        }
         int get_count(const string &w)const{
            Node* curNode = head;
            while (curNode != nullptr){
                if (curNode->word == w){ //If current node is the same as the parameter we return the count
                    return curNode->count;
                }
                else{
                    curNode = curNode->next;
                }
            }
            return 0;
        }


        int num_different_words()const{
            int total = 0;
            Node*curNode = head;
           
            while(curNode!=nullptr){ //LL copmrised of only unique words, we count number of nodes
                total++;
                curNode = curNode->next;
            }
            return total;
        }

        int total_words()const{
            int total = 0;
            Node*curNode = head;
            
            while(curNode!=nullptr){
                total+=curNode->count; // add the count of each node, gives us summation of all total instances of each word
                curNode = curNode->next;
            }
            return total;
        }

        bool is_sorted()const{
            
            if (head == nullptr) { // return true if list is empty
                return true; 
                }
            
            Node*curNode = head; 
            while(curNode->next!=nullptr){
                if (curNode->word > curNode->next->word) // using ASCII format if the upcoming word if the next word is alphabetically less than current we return false
                {
                    return false;
                }
                curNode=curNode->next;
            }
            
            return true;
        }
        
        string most_frequent()const{
            int max = 0;
            string ret;

            Node*curNode = head;
            while(curNode!=nullptr){
                if(curNode->count> max){
                    ret = curNode->word; // loops through and sets ret as the word with largest count
                    max = curNode->count; // sets new count to be  tested against
                }
            curNode = curNode->next;
            }
            return ret;
        }
        int num_singletons()const{
            int total = 0;
            Node*curNode = head;

            while(curNode!=nullptr){ //every time we have a node with count 1 add it to total
                if(curNode->count == 1){
                    total++;
                }
                curNode = curNode->next;
            }
            return total;
        }
        void add_word(const string &w){
            Node* curNode = head;
            while(curNode != nullptr){// loop through linked list
                if(curNode->word == w){ 
                    curNode->count++; //if word in the the list then add to count
                    break; //leave loop
                    }
                curNode = curNode->next;
                }
            if(curNode==nullptr){ // create new node given the word
                Node* newnode = new Node;
                newnode->word = w;
                newnode->count = 1;
                newnode->next = nullptr;

                if(head == nullptr || w<head->word){ //if list is empty or new node should go before head
                    newnode->next = head;
                    head = newnode;
                }     
                else {
                    curNode = head;
                    while (curNode->next != nullptr && curNode->next->word<w) { // goes to a point in the list wehre the next node is greater than w but curnode is less than
                        curNode = curNode->next;
                        ;

                    }
                    newnode->next = curNode->next; // palces new node in between the 2 nodes
                    curNode->next = newnode;
            
                    }
            }
        }
        void print_words()const{ //loops through entire list printing the word and ocunt
            Node*curNode = head;
            
            while(curNode!=nullptr){
                cout << "{" << "\""<< curNode->word<<"\"" <<curNode->count << "}"<<endl;
                curNode = curNode->next;
            }
        } 

    ~Wordlist(){ //clears and frees entire list
        Node* curNode = head;
        Node* del = head;
        
        while (curNode->next != nullptr)
        {
            del = curNode; // set node to delete with temp pointer
            curNode = curNode->next;// iterate 
            delete del; // delete the temp pointer
        }
        delete curNode;
    }


}; 
