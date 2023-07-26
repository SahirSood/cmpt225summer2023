// a5_main.cpp

#include "Wordlist.h"

//
// test_read() is a helper function that reads words, one at a time, from cin,
// into a Wordlist and print the stats. You can use it to help test your
// Wordlist class, e.g.:
//
//    > make a5_main
//    g++ -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g   a5_main.cpp   -o a5_main
//   
//    > ./a5_main < tiny_shakespeare.txt
//    Number of different words: 25670
//        Total number of words: 202651
//           Most frequent word: the 5437
//         Number of singletons: 14919 (58%)
//
void test_read()
{
    Wordlist lst("small.txt");
    string w;
    cout<<"list created"<<endl;
    
    // while (cin >> w)
    // {
    //     lst.add_word(w);
    // }
    // cout<<"----------------------------------------------"<<endl;
    lst.print_stats();
}
void test_wordlist()
{
    Wordlist lst("small.txt");
    assert(lst.num_different_words() == 7);

    assert(lst.total_words() == 9);

    assert(lst.is_sorted());

    assert(!lst.contains("This"));

    cout << "... test_wordlist() done: all tests passed!\n";
}
int main()
{
    cout << "Welcome to assignment 5!\n";
    test_read();
}
