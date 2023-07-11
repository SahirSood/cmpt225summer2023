// test_sorts.cpp

//
// Test all the sorts in sort_implementation.h. 
//
// Ignores the SortStats object returned by the sort functions.
//

#include "a4_base.h"
#include "a4_sort_implementations.h"
#include "test.h"
#include <cassert>
#include <string>
#include <fstream>

using namespace std;

void test_is_sorted_int()
{
    Test("test_is_sorted_int");
    vector<int> v;
    assert(is_sorted(v));
    v = {2};
    assert(is_sorted(v));
    v = {2, 1};
    assert(!is_sorted(v));
    v = {1, 2};
    assert(is_sorted(v));
    v = {2, 2};
    assert(is_sorted(v));
    v = {1, 2, 3};
    assert(is_sorted(v));
    v = {1, 3, 2};
    assert(!is_sorted(v));
    v = {3, 2, 1};
    assert(!is_sorted(v));
    v = {1, 2, 2};
    assert(is_sorted(v));
    v = {2, 2, 2};
    assert(is_sorted(v));
    v = {2, 2, 1};
    assert(!is_sorted(v));
    v = {2, 2, 3};
    assert(is_sorted(v));
}

void test_is_sorted_string()
{
    Test("test_is_sorted_string");
    vector<string> v;
    assert(is_sorted(v));
    v = {"b"};
    assert(is_sorted(v));
    v = {"b", "a"};
    assert(!is_sorted(v));
    v = {"a", "b"};
    assert(is_sorted(v));
    v = {"b", "b"};
    assert(is_sorted(v));
    v = {"a", "b", "c"};
    assert(is_sorted(v));
    v = {"a", "c", "b"};
    assert(!is_sorted(v));
    v = {"c", "b", "a"};
    assert(!is_sorted(v));
    v = {"a", "b", "b"};
    assert(is_sorted(v));
    v = {"b", "b", "b"};
    assert(is_sorted(v));
    v = {"b", "b", "a"};
    assert(!is_sorted(v));
    v = {"b", "b", "c"};
    assert(is_sorted(v));
}

void test_bubble_sort_int()
{
    Test("test_bubble_sort_int");
    vector<int> v;
    assert(v.size() == 0);
    bubble_sort(v);
    assert(is_sorted(v));
    v = {2};
    bubble_sort(v);
    assert(is_sorted(v));
    v = {2, 1};
    bubble_sort(v);
    assert(is_sorted(v));
    bubble_sort(v);
    assert(is_sorted(v));
    v = {2, 1, 0};
    bubble_sort(v);
    assert(is_sorted(v));
}

void test_bubble_sort_string()
{
    Test("test_bubble_sort_string");
    vector<string> v;
    assert(v.size() == 0);
    bubble_sort(v);
    assert(is_sorted(v));
    v = {"b"};
    bubble_sort(v);
    assert(is_sorted(v));
    v = {"b", "a"};
    bubble_sort(v);
    assert(is_sorted(v));
    bubble_sort(v);
    assert(is_sorted(v));
    v = {"b", "a", "c"};
    bubble_sort(v);
    assert(is_sorted(v));
    v = {"a", "b", "c"};
    bubble_sort(v);
    assert(is_sorted(v));
}

void test_insertion_sort_int()
{
    Test("test_insertion_sort_int");
    vector<int> v;
    assert(v.size() == 0);
    insertion_sort(v);
    assert(is_sorted(v));
    v = {2};
    insertion_sort(v);
    assert(is_sorted(v));
    v = {2, 1};
    insertion_sort(v);
    assert(is_sorted(v));
    insertion_sort(v);
    assert(is_sorted(v));
    v = {2, 1, 0};
    insertion_sort(v);
    assert(is_sorted(v));
}

void test_insertion_sort_string()
{
    Test("test_insertion_sort_string");
    vector<string> v;
    assert(v.size() == 0);
    insertion_sort(v);
    assert(is_sorted(v));
    v = {"b"};
    insertion_sort(v);
    assert(is_sorted(v));
    v = {"b", "a"};
    insertion_sort(v);
    assert(is_sorted(v));
    insertion_sort(v);
    assert(is_sorted(v));
    v = {"b", "a", "c"};
    insertion_sort(v);
    assert(is_sorted(v));
    v = {"a", "b", "c"};
    insertion_sort(v);
    assert(is_sorted(v));
}

void test_selection_sort_int()
{
    Test("test_selection_sort_int");
    vector<int> v;
    assert(v.size() == 0);
    selection_sort(v);
    assert(is_sorted(v));
    v = {2};
    selection_sort(v);
    assert(is_sorted(v));
    v = {2, 1};
    selection_sort(v);
    assert(is_sorted(v));
    selection_sort(v);
    assert(is_sorted(v));
    v = {2, 1, 0};
    selection_sort(v);
    assert(is_sorted(v));

}

void test_selection_sort_string()
{
    Test("test_selection_sort_string");
    vector<string> v;
    assert(v.size() == 0);
    selection_sort(v);
    assert(is_sorted(v));
    v = {"b"};
    selection_sort(v);
    assert(is_sorted(v));
    v = {"b", "a"};
    selection_sort(v);
    assert(is_sorted(v));
    selection_sort(v);
    assert(is_sorted(v));
    v = {"b", "a", "c"};
    selection_sort(v);
    assert(is_sorted(v));
    v = {"a", "b", "c"};
    selection_sort(v);
    assert(is_sorted(v));
}

void test_merge_sort_int()
{
    Test("test_merge_sort_int");
    vector<int> v;
    assert(v.size() == 0);
    merge_sort(v);
    assert(is_sorted(v));
    v = {2};
    merge_sort(v);
    assert(is_sorted(v));
    v = {2, 1};
    merge_sort(v);
    assert(is_sorted(v));
    merge_sort(v);
    assert(is_sorted(v));
    v = {2, 1, 0};
    merge_sort(v);
    assert(is_sorted(v));
}

void test_merge_sort_string()
{
    Test("test_merge_sort_string");
    vector<string> v;
    assert(v.size() == 0);
    merge_sort(v);
    assert(is_sorted(v));
    v = {"b"};
    merge_sort(v);
    assert(is_sorted(v));
    v = {"b", "a"};
    merge_sort(v);
    assert(is_sorted(v));
    merge_sort(v);
    assert(is_sorted(v));
    v = {"b", "a", "c"};
    merge_sort(v);
    assert(is_sorted(v));
    v = {"a", "b", "c"};
    merge_sort(v);
    assert(is_sorted(v));
}

void test_quick_sort_int()
{
    Test("test_quick_sort_int");
    vector<int> v;
    assert(v.size() == 0);
    quick_sort(v);
    assert(is_sorted(v));
    v = {2};
    quick_sort(v);
    assert(is_sorted(v));
    v = {2, 1};
    quick_sort(v);
    assert(is_sorted(v));
    quick_sort(v);
    assert(is_sorted(v));
    v = {2, 1, 0};
    quick_sort(v);
    assert(is_sorted(v));
}

void test_quick_sort_string()
{
    Test("test_quick_sort_string");
    vector<string> v;
    assert(v.size() == 0);
    quick_sort(v);
    assert(is_sorted(v));
    v = {"b"};
    quick_sort(v);
    assert(is_sorted(v));
    v = {"b", "a"};
    quick_sort(v);
    assert(is_sorted(v));
    quick_sort(v);
    assert(is_sorted(v));
    v = {"b", "a", "c"};
    quick_sort(v);
    assert(is_sorted(v));
    v = {"a", "b", "c"};
    quick_sort(v);
    assert(is_sorted(v));
}

void test_shell_sort_int()
{
    Test("test_shell_sort_int");
    vector<int> v;
    assert(v.size() == 0);
    shell_sort(v);
    assert(is_sorted(v));
    v = {2};
    shell_sort(v);
    assert(is_sorted(v));
    v = {2, 1};
    shell_sort(v);
    assert(is_sorted(v));
    shell_sort(v);
    assert(is_sorted(v));
    v = {2, 1, 0};
    shell_sort(v);
    assert(is_sorted(v));
}

void test_shell_sort_string()
{
    Test("test_shell_sort_string");
    vector<string> v;
    assert(v.size() == 0);
    shell_sort(v);
    assert(is_sorted(v));
    v = {"b"};
    shell_sort(v);
    assert(is_sorted(v));
    v = {"b", "a"};
    shell_sort(v);
    assert(is_sorted(v));
    shell_sort(v);
    assert(is_sorted(v));
    v = {"b", "a", "c"};
    shell_sort(v);
    assert(is_sorted(v));
    v = {"a", "b", "c"};
    shell_sort(v);
    assert(is_sorted(v));
}

void test_iquick_sort_int()
{
    Test("test_iquick_sort_int");
    vector<int> v;
    assert(v.size() == 0);
    iquick_sort(v);
    assert(is_sorted(v));
    v = {2};
    iquick_sort(v);
    assert(is_sorted(v));
    v = {2, 1};
    iquick_sort(v);
    assert(is_sorted(v));
    iquick_sort(v);
    assert(is_sorted(v));
    v = {2, 1, 0};
    iquick_sort(v);
    assert(is_sorted(v));
}

void test_iquick_sort_string()
{
    Test("test_iquick_sort_string");
    vector<string> v;
    assert(v.size() == 0);
    iquick_sort(v);
    assert(is_sorted(v));
    v = {"b"};
    iquick_sort(v);
    assert(is_sorted(v));
    v = {"b", "a"};
    iquick_sort(v);
    assert(is_sorted(v));
    iquick_sort(v);
    assert(is_sorted(v));
    v = {"b", "a", "c"};
    iquick_sort(v);
    assert(is_sorted(v));
    v = {"a", "b", "c"};
    iquick_sort(v);
    assert(is_sorted(v));
}
void bubble_sort_test(ofstream &out)
    {
        for (int i = 2000; i <= 50000; i += 2000)
        {
            vector<int> random_vector = rand_vec(i, 1, i);
            SortStats stats = bubble_sort(random_vector);
            cout << stats.to_csv() << endl;
            out<<stats.to_csv()<<endl;
        }
    };
void insertion_sort_test(ofstream &out)
    {
        for (int i = 2000; i <= 50000; i += 2000)
        {
            vector<int> random_vector = rand_vec(i, 1, i);
            SortStats stats = insertion_sort(random_vector);
            cout << stats.to_csv() << endl;
            out<<stats.to_csv()<<endl;
        }
    };
void selection_sort_test(ofstream &out)
    {
        for (int i = 2000; i <= 50000; i += 2000)
        {
            vector<int> random_vector = rand_vec(i, 1, i);
            SortStats stats = selection_sort(random_vector);
            cout << stats.to_csv() << endl;
            out<<stats.to_csv()<<endl;
        }
    };
void quick_sort_test(ofstream &out)
    {
        for (int i = 2000; i <= 50000; i += 2000)
        {
            vector<int> random_vector = rand_vec(i, 1, i);
            SortStats stats = quick_sort(random_vector);
            cout << stats.to_csv() << endl;
            out<<stats.to_csv()<<endl;
        }
    };
void merge_sort_test(ofstream &out)
    {
        for (int i = 2000; i <= 50000; i += 2000)
        {
            vector<int> random_vector = rand_vec(i, 1, i);
            SortStats stats = merge_sort(random_vector);
            cout << stats.to_csv() << endl;
            out<<stats.to_csv()<<endl;
        }
    };

void i_quick_sort_test(ofstream &out)
    {
        for (int i = 2000; i <= 50000; i += 2000)
        {
            vector<int> random_vector = rand_vec(i, 1, i);
            SortStats stats = iquick_sort(random_vector);
            cout << stats.to_csv() << endl;
            out<<stats.to_csv()<<endl;
        }
    };
void shell_sort_test(ofstream &out)
    {
        for (int i = 2000; i <= 50000; i += 2000)
        {
            vector<int> random_vector = rand_vec(i, 1, i);
            SortStats stats = shell_sort(random_vector);
            cout << stats.to_csv() << endl;
            out<<stats.to_csv()<<endl;
        }
    };

int main()
{
    test_is_sorted_int();
    test_is_sorted_string();

    test_bubble_sort_int();
    test_bubble_sort_string();

    test_insertion_sort_int();
    test_insertion_sort_string();

    test_selection_sort_int();
    test_selection_sort_string();

    test_merge_sort_int();
    test_merge_sort_string();

    test_quick_sort_int();
    test_quick_sort_string();

    test_shell_sort_int();
    test_shell_sort_string();

    test_iquick_sort_int();
    test_iquick_sort_string();

    cout << "\nall sorting tests passed!" << endl;

    ofstream outFile("TestFile.csv");


    // bubble_sort_test(outFile);
    // insertion_sort_test(outFile);
    // selection_sort_test(outFile);
    merge_sort_test(outFile);
    quick_sort_test(outFile);
    shell_sort_test(outFile);
    i_quick_sort_test(outFile);

} // main


