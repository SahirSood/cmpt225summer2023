// a4_sort_implementations.h

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
        num_comps++;
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
            num_comps++;
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
//Helper for mergeSort
int mergeSorting(vector<int>&left, vector<int>& right, vector<int>& vs)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    int n =0;

    while (j < nL && k < nR) 
    {
        n++;
        if (left[j] < right[k]) {
            vs[i] = left[j];
            j++;
        }
        else {
            vs[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        vs[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        vs[i] = right[k];
        k++; i++;
    }
}

template <typename T>
SortStats merge_sort(vector<T> &v){
    ulong num_comps = 0;
    clock_t start= clock();
    
    if (v.size() <= 1) {
        return;}

    int mid = v.size() / 2;
    vector<int> left;
    vector<int> right;

    for (size_t j = 0; j < mid;j++)
        left.push_back(v[j]);
    for (size_t j = 0; j < (v.size()) - mid; j++)
        right.push_back(v[mid + j]);

    sort(left);
    sort(right);
    num_comps = (left, right, v);
    
    clock_t end= clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return SortStats{"Merge Sort",
                    v.size(),
                    num_comps,
                    elapsed_cpu_time_sec}
}



//Helper Fuction for quicksort
int Partition(vector<int> &v, int start, int end, int* comps){
	
	int pivot = end;
	int j = start;
	for(int i=start;i<end;++i){
        *comps++;
        if(v[i]<v[pivot]){
			swap(v[i],v[j]);
			++j;
		}
	}
	swap(v[j],v[pivot]);
	return j;
}

//second helper for Quick sort
template <typename T>
void quick_sort_main(vector<T> &v, int start, int end, int* comps){
    if(start<end){
        int p = Partition(v,start,end);
        quick_sort_main(v,start,p-1, comps);
        quick_sort_main(v,p+1,end,comps);
    }
}

template <typename T>
SortStats quick_sort(vector<T> &v){
    clock_t start = clock();
    ulong num_comps = 0;
    quick_sort_main(v,0,v.size()-1,&num_comps);
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Quick Sort",
                    v.size(),
                    num_comps,
                    elapsed_cpu_time_sec}
}




template <typename T>
SortStats shell_sort(vector<T> &v){
    clock_t start = clock();
    ulong num_comps = 0;
    int n = v.size();

    for(int gap = n/2; gap>0;gap/=2){
        for(int i = gap;i<n;i++){
            int temp = v[i];

            for(int j=i;j>=gap && v[j-gap]>temp; j-=gap){
                v[j]=v[j-gap];
                num_comps++;
            }
            v[j] = temp;
        }
    }
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Shell Sort",
                    v.size(),
                    num_comps,
                    elapsed_cpu_time_sec}
}


template <typename T>
SortStats iquick_sort(vector<T> &v);
// See description in assignment.

//
// Returns a vector of n randomly chosen ints, each <= max and >= min.
//
vector<int> rand_vec(int n, int min, int max);
