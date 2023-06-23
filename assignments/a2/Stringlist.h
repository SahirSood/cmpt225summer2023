// Stringlist.h

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
// Do not use any other #includes or #pragmas in this file.
//

#pragma once

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

class Stringlist
{
    //Stack that holds strings as its data
    struct Node {
    string data;
    struct Node *next;
    };
    // initialize the stack by making the top = nullptr
    struct Node* Top = nullptr;



    int cap;     // capacity
    string *arr; // array of strings
    int sz;      // size
    
    //flags so code can keep tracking of what is calling what.
    bool calledFromUndo = false;
    bool ishelper = false;


    //
    // Helper function for throwing out_of_range exceptions.
    //
    void bounds_error(const string &s) const
    {
        throw out_of_range("Stringlist::" + s + " index out of bounds");
    }

    //
    // Helper function for checking index bounds.
    //
    void check_bounds(const string &s, int i) const
    {
        if (i < 0 || i >= sz)
            bounds_error(s);
    }

    //
    // Helper function for copying another array of strings.
    //
    void copy(const string *other)
    {
        for (int i = 0; i < sz; i++)
        {
            arr[i] = other[i];
        }
    }

    //
    // Helper function for checking capacity; doubles size of the underlying
    // array if necessary.
    //
    void check_capacity()
    {
        if (sz == cap)
        {
            cap *= 2;
            string *temp = new string[cap];
            for (int i = 0; i < sz; i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }
    }

public:
    //
    // Default constructor: makes an empty StringList.
    //
    Stringlist()
        : cap(10), arr(new string[cap]), sz(0)
    {

    }
    //
    // Copy constructor: makes a copy of the given StringList.
    //
    // Does *not* copy the undo stack, or any undo information from other.
    //
    Stringlist(const Stringlist &other)
        : cap(other.cap), arr(new string[cap]), sz(other.sz)
    {
        copy(other.arr);
    }

    //
    // destructor
    //
    ~Stringlist()
    {
        delete[] arr;

    }

    // Takes in a string and assigns it to a new node
    // makes the new node the top of the stack
    void push(string call){
        Node* newnode = new Node;
        newnode->data = call;
        newnode->next = Top;
        Top = newnode;
    }

    //takes the string at the top of the stack and returns it while also deleting it from memory
    string pop(){
        if(Top == nullptr){
            return nullptr;
        }

        string ret = Top -> data;
        Node* temp = Top;
        Top = Top->next;
        delete temp;

        return ret; 
    }


    //
    // Assignment operator: makes a copy of the given StringList.
    //
    // undoable
    //
    // For undoing, when assignment different lists, the undo stack is not
    // copied:
    //
    //    lst1 = lst2; // lst1 undo stack is updated to be able to undo the //
    //    assignment; lst1 does not copy lst2's stack
    //    //
    //    // lst2 is not change in any way
    //
    // Self-assignment is when you assign a list to itself:
    //
    //    lst1 = lst1;
    //
    // In this case, nothing happens to lst1. Nothing is changed. Both its
    // string data and undo stack are left as-is.
    //
    Stringlist &operator=(const Stringlist &other)
    {
        if (this != &other)
        {
            delete[] arr;
            cap = other.capacity();
            arr = new string[cap];
            sz = other.size();
            copy(other.arr);
        }
        return *this;
    }

    //
    // Returns the number of strings in the list.
    //
    int size() const { return sz; }

    //
    // Returns true if the list is empty, false otherwise.
    //
    bool empty() const { return size() == 0; }

    //
    // Returns the capacity of the list, i.e. the size of the underlying array.
    //
    int capacity() const { return cap; }

    //
    // Returns the string at the given index.
    //

    string get(int index) const
    {
        check_bounds("get", index);     
        return arr[index];
    }

    //
    // Returns the index of the first occurrence of s in the list, or -1 if s is
    // not in the lst.
    //
    int index_of(const string &s) const
    {
        for (int i = 0; i < sz; i++)
        {
            if (arr[i] == s)
            {
                return i;
            }
        }
        return -1;
    }

    //
    // Returns true if s is in the list, false otherwise.
    //
    bool contains(const string &s) const
    {
        return index_of(s) != -1;
    }

    //
    // Returns a string representation of the list.
    //
    string to_string() const
    {
        string result = "{";
        for (int i = 0; i < size(); i++)
        {
            if (i > 0)
                result += ", ";
            result += "\"" + get(i) + "\"";
        }
        return result + "}";
    }

    //
    // Sets the string at the given index.
    //
    // undoable
    //
    void set(int index, string value)
    {
        check_bounds("set", index);
        // saves variable before we delete it
        string keep = arr[index];
        arr[index] = value;

        //If set is not called because we need to undo something then it pushes the opposite function to the stack.
        if (calledFromUndo != true){
            string ret = "set " + std::to_string(index) + " " + keep;
            push(ret);}

        //resets flag
        calledFromUndo = false;
    }   

    //
    // Insert s before index; if necessary, the capacity of the underlying array
    // is doubled.
    //
    // undoable
    //
    void insert_before(int index, const string &s)
    {
        if (index < 0 || index > sz) // allows insert at end, i == sz
            bounds_error("insert_before");
        check_capacity();

        for (int i = sz; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[index] = s;
        sz++;
                
        //If insert_before  is not called because we need to undo something then it pushes the opposite function to the stack.
        // Also makes sure it isnt being used as a helper functino because insert_back uses this function
        if (calledFromUndo != true && ishelper != true){
            string ret = "remove_at " + std::to_string(index);
            push(ret);}
        calledFromUndo = false;

    }

    //
    // Appends s to the end of the list; if necessary, the capacity of the
    // underlying array is doubled.
    //
    // undoable
    //
    void insert_back(const string &s)
    {

        // before calling insert_before, it tells the code its a helper 
        ishelper = true;
        insert_before(size(), s);
        
        //if not being called for the purpose of undoing another function
        if (calledFromUndo != true){
            string ret = "remove_at " + std::to_string(size()-1);
            push(ret);
        }
        //resets flags
        calledFromUndo = false;
        ishelper = false;

    }

    //
    // Inserts s at the front of the list; if necessary, the capacity of the
    // underlying array is doubled.
    //
    // undoable
    //
    void insert_front(const string &s)
    {

        // before calling insert_before, it tells the code its a helper 
        ishelper = true;
        insert_before(0, s);
        
        // ensures we are not being called for the sake of undoing a previous function.
        if (calledFromUndo != true){
            string ret = "remove_at " + std::to_string(0);
            push(ret);}
        
        // reset flags
        ishelper = false;
        calledFromUndo = false;
    }

    //
    // Removes the string at the given index; doesn't change the capacity.
    //
    // undoable
    //
    void remove_at(int index)
    {
        check_bounds("remove_at", index);
        
        //string we want to keep
        string keep = arr[index];

        for (int i = index; i < sz - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        sz--;
        
        //makes sure we are not being called to undo a previous function.
        if (calledFromUndo != true && ishelper != true){
            string ret = "insert_before " + std::to_string(index) + keep;
            push(ret);
        }
        calledFromUndo = false;

    }

    //
    // Removes all strings from the list; doesn't change the capacity.
    //
    // undoable
    //
    void remove_all()
    {
        int retSize = sz;

        //string where we will store all the words
        string result;

        // every word in the array will be saved to result seperated by a whitespace
        for (int i = 0; i < sz; i++) {
            result += arr[i];
            if (i < sz) {
                result += " ";
            }
        }


        // so code knows that remove_at is a helper function.
        ishelper = true;
        while (sz > 0)
        {
            remove_at(sz - 1);
        } 

        if (calledFromUndo != true){
            string ret = "redo_all " + std::to_string(retSize) + " " + result;
            push(ret);
        }

        //reset flags
        calledFromUndo = false;
        ishelper = false;


    }

    //
    // Removes the first occurrence of s in the list, and returns true. If s is
    // nowhere in the list, nothing is removed and false is returned.
    //
    // undoable
    //
    bool remove_first(const string &s)
    {
        int index = index_of(s);
        if (index == -1)
            return false;
        
        // makes sure we are not called to undo antoehr function.
        if (calledFromUndo != true){
            string ret = "insert_before " + std::to_string(index) + s;
            push(ret);
         }
        // so remove_at knows it is a helper function
        ishelper = true;
        remove_at(index);
        
        //reset flags.
        calledFromUndo = false;
        ishelper = false;
        return true;
    }

    //
    // Undoes the last operation that modified the list. Returns true if a
    // change was undone.
    //
    // If there is nothing to undo, does nothing and returns false.
    //
    bool undo()
    {

        //variables to store substrings of what we pushed
        string command;
        int index;
        string keep;

        // store the instruction
        string instruction = pop();
        // finds the first whitespace and saves all the letters from idnex 0 to the whitespace as the command
        size_t firstspace = instruction.find(' ');
        command = instruction.substr(0,firstspace);

        // from the first whitespace to second whitespace this is the index
        size_t  secondspace = instruction.find(' ', firstspace + 1);
        string indexstr = instruction.substr(firstspace + 1, secondspace - firstspace - 1);
        index = stoi(indexstr);

        // the string we are transferring is to the end
        keep = instruction.substr(secondspace+1);

        calledFromUndo = true;
        if(command == "set"){
            set(index,keep);
            return true;
        }
        else if(command == "remove_at"){
            remove_at(index);
            return true;
        }
        else if(command == "insert_before"){
            insert_before(index, keep);
            return true;
        }
        else if(command == "redo_all"){
            int j = -1;
            cout<<"enters"<<endl;
            for (int i = 0; i < index; i++)
            {
                j++;
                int startPos = j;  // Starting position of the substring
                // Find the position of the next space character
                int endPos = keep.find(' ', j);
                if (endPos == string::npos)
                {
                    // If no space character is found, break or handle it accordingly
                    break;
                }
                int length = endPos - startPos;  // Length of the substring
                cout<<keep.substr(startPos, length)<<endl;
                arr[i] = keep.substr(startPos, length);  // Extract the substring and assign it to arr
                j = endPos;  // Update the current position
                // You can optionally handle any additional logic here if needed
            }

            return true;        
         }
         return false;
    }
}; // class Stringlist

//
// Prints list to in the format {"a", "b", "c"}.
//
ostream &operator<<(ostream &os, const Stringlist &lst)
{
    return os << lst.to_string();
}

//
// Returns true if the two lists are equal, false otherwise.
//
// Does *not* consider any undo information when comparing two Stringlists. All
// that matters is that they have the same strings in the same order.
//
bool operator==(const Stringlist &a, const Stringlist &b)
{
    if (a.size() != b.size())
    {
        return false;
    }
    for (int i = 0; i < a.size(); i++)
    {
        if (a.get(i) != b.get(i))
        {
            return false;
        }
    }
    return true;
}

//
// Returns true if the two lists are not equal, false otherwise.
//
// Does *not* consider any undo information when comparing two Stringlists.
//
bool operator!=(const Stringlist &a, const Stringlist &b)
{
    return !(a == b);
}   