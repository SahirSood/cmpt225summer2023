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
            
            Node* newnode = new Node;
            head = newnode;
            Node* curNode = head;

            std::string line_;
            ifstream file_(file_name);
            if(file_.is_open())
            {
                while(getline(file_, line_)){
                    if(contains(line_)){
                        
                    }
                   
                    else{
                        curNode ->word = line_;
                        newnode= new Node;
                        curNode->next = newnode;
                        newnode = nullptr;}
                    }
                file_.close();
            }
            else{
                cerr << "Error opening file: " << file_name << endl;

            }
        }


        int get_count(const string &w){
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


        int num_different_words(){

        }

        int total_words(){

        }

        bool is_sorted(){

        }
        
        string most_frequent(){

        }
        int num_singletons(){
            
        }

    ~Wordlist(){

    }

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
