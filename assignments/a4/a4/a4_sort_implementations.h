// a4_sort_implementations.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <put your full name here!>
// St.# : <put your full SFU student number here>
// Email: <put your SFU email address here>
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

#pragma once

#include "a4_base.h"

using namespace std;

//
// Put the implementations of all the functions listed in a4_base.h here.

template <typename T>
SortStats bubble_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock(); 

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            num_comps++; // <--- num_comps is incremented here
            if (v[j] > v[j + 1])
            {
                T temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Bubble sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

template <typename T>
SortStats insertion_sort(vector<T> &v)
{
    ulong num_comps = 0;
    clock_t start = clock();

    int i,j,tmp;
    for(i=1;i<v.size();i++)
    {
        j=i;
        tmp = v[i];
        while (j>0 && tmp<v[j-1])
        {
            num_comps++;
            v[j]=v[j-1];
            j--;
        }
        v[j] = tmp;
        clock_t end = clock();
        double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

        return SortStats{"Insertion Sort",
                        v.size(),
                        num_comps,
                        elapsed_cpu_time_sec}
    }

}

template <typename T>
SortStats selection_sort(vector<T> &v){
    ulong num_comps = 0;
    clock_t start = clock();

    int temp;
    for (int i = 0; i < v.size() - 1; i++)
    {
        int vectMin = i;
        for (int j = i + 1; j < v.size(); j++)
        {
            if(v[j] < v[vectMin])
            {
                vectMin = j;
            }
        }
        temp = v[i];
        v[i] = v[vectMin];
        v[vectMin] = temp;
    }
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return SortStats{"Selection Sort",
                    v.size(),
                    num_comps,
                    elapsed_cpu_time_sec}
}
//
