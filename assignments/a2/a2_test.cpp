// Stringlist_test.cpp

#include "Stringlist.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

struct Test
{
    string name;
    Test(const string &name)
        : name(name)
    {
        cout << "Calling " << name << " ...\n";
    }

    ~Test()
    {
        cout << "... " << name << " done: all tests passed\n";
    }
}; // struct Test



void test_copy_constructor()
{
    Test("test_copy_constructor");
    Stringlist lst;
    Stringlist lst2(lst);
    assert(lst == lst2);

    lst.insert_back("A");
    lst.insert_back("B");
    lst.insert_back("C");
    assert(lst.size() == 3);
    assert(lst.get(0) == "A");
    assert(lst.get(1) == "B");
    assert(lst.get(2) == "C");
    assert(lst.to_string() == "{\"A\", \"B\", \"C\"}");

    lst.undo();
    assert(lst.to_string() =="{\"A\", \"B\"}");
    lst.undo();
    assert(lst.to_string() == "{\"A\"}");

    lst.insert_front("pineapple");
    assert(lst.to_string()=="{\"pineapple\", \"A\"}");
    lst.insert_front("belong");
    cout<<lst<<endl;
    assert(lst.to_string()=="{\"belong\", \"pineapple\", \"A\"}");
    lst.undo();
    cout<<lst<<endl;
    assert(lst.to_string()=="{\"pineapple\", \"A\"}");


    lst.insert_back("plan");
    lst.insert_back("is");
    lst.insert_back("pizza");
    lst.insert_back("apple");
    lst.insert_back("pizza");

    assert(lst.to_string()=="{\"pineapple\", \"A\", \"plan\", \"is\", \"pizza\", \"apple\", \"pizza\"}");

    lst.insert_before(3, "insert");
    assert(lst.to_string()=="{\"pineapple\", \"A\", \"plan\", \"insert\", \"is\", \"pizza\", \"apple\", \"pizza\"}");
    lst.insert_before(3, "again");
    cout<<lst<<"before undo"<<endl;
    lst.undo();
    lst.undo();
    cout<<lst<<endl;
    assert(lst.to_string()=="{\"pineapple\", \"A\", \"plan\", \"is\", \"pizza\", \"apple\", \"pizza\"}");
    lst.undo();
    lst.undo();
    lst.undo();
    assert((lst.to_string()=="{\"pineapple\", \"A\", \"plan\", \"is\"}"));
    lst.remove_all();
    lst.undo();
    cout<<"the remade list"<<lst.to_string()<<endl;
    assert((lst.to_string()=="{\"pineapple\", \"A\", \"plan\", \"is\"}"));








    

}







int main()
{
    test_copy_constructor();

    cout << "\nAll Stringlist tests passed!\n";
} // main
