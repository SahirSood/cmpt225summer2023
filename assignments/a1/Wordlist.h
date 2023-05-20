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

        Wordlist(){}

        Wordlist (string file_name){
            
            Node* newnode;
            std::string word_;
            ifstream file_(file_name);
            if(file_.is_open())
            {
                while(file_ >> word_){
                    Node* curNode = head;
                    while(curNode != nullptr){
                        if(curNode->word == word_){
                            curNode->count++;
                            break;
                            }
                        curNode = curNode->next;
                        }
                    if(curNode==nullptr){
                        newnode = new Node;
                        newnode->word = word_;
                        newnode->count = 1;
                        newnode->next = nullptr;
                        if(head== curNode){
                            head = newnode;
                        }     
                        else {
                            curNode = head;
                            while (curNode->next != nullptr) {
                                curNode = curNode->next;
                            }
                            curNode->next = newnode;
                         }
                    }
                 }
                file_.close();
            }
            else{
                cerr << "Error opening file: " << file_name << endl;\
            }
        }
         int get_count(const string &w)const{
            Node* curNode = head;
            while (curNode != nullptr){
                if (curNode->word == w){
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
            while(curNode!=nullptr){
                total++;
                curNode = curNode->next;
            }
            return total;
        }

        int total_words()const{
            int total = 0;
            Node*curNode = head;
            while(curNode!=nullptr){
                total+=curNode->count;
                curNode = curNode->next;
            }
            return total;
        }

        bool is_sorted()const{
            return 0;
        }
        
        string most_frequent()const{
            int max = 0;
            string ret;

            Node*curNode = head;
            while(curNode!=nullptr){
                if(curNode->count> max){
                    ret = curNode->word;
                    max = curNode->count;
                }
            curNode = curNode->next;
            }
            return ret;
        }
        int num_singletons()const{
            int total = 0;
            Node*curNode = head;
            while(curNode!=nullptr){
                if(curNode->count == 1){
                    total++;
                }
            }
            return total;
        }
        void add_word(const string &w)const{
            return;
        }

        void print_words()const{};

    ~Wordlist(){}

    //
    // ... you can write helper methods if you need them ...
    //

    //
    // ... write a default constructor that creates an empty Wordlist ...
    //

}; // class Wordlist

//
// ... you can write helper functions here (or before Wordlist) if you need them
// ...
//

//
// ... write functions to test every method of Wordlist ...
//
