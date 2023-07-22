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

//Returns True if given vector is in increasing order
// if not in order then returns false
bool is_sorted(vector<T> &v){
    int n = v.size();
    if(n ==0){
        return true;
    }
    
    for (int i = 1; i < n; i++)
    {
        //if element before current element is larger we return false
        if (v[i]<v[i-1])
        {
            return false;
        }
    }
    //returns true if every element is larger than the previous
    return true;
}

//bubble sort sorting algroithm
template <typename T>
SortStats bubble_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();  //<-----clock start time 


    //iterates trhough every element
    //after each ith iteration we will place next biggest element towards end of vector
    for (int i = 0; i < v.size(); i++)
    {
        //Now comparing each element to the next, we will swap if the next is less than current v[j]
        //after all swaps max element will be at end of vector 
        for (int j = 0; j < v.size() - 1; j++)
        {
            num_comps++; // <--- num_comps is incremented here
            if (v[j] > v[j + 1]) 
            {
                //swapping elements
                T temp = v[j]; 
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    
    clock_t end = clock(); //<<-- clock end time
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC; //<<-- calc total time
    
    return SortStats{"Bubble sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}


//Insortion sort sorting algorithm for vectors
template <typename T>
SortStats insertion_sort(vector<T> &v)
{
    ulong num_comps = 0;// <--- num_comps is initialized to 0 here
    clock_t start = clock(); // Clock start time saved

    int i,j;
    T tmp;

    //iteration thorugh every element
    for(i=1;i<v.size();i++)
    {
        j=i;
        tmp = v[i];
        num_comps++;// <--- num_comps is incremented here
        
        //for each element we move backwards in the vector
        //we insert the ith element to a posistion where it is greater than all elemenets before it
        while (j>0 && tmp<v[j-1])
        {
            num_comps++;// <--- num_comps is incremented here
            v[j]=v[j-1];
            j--;
        }
        //assigns the ith element to where we stop
        v[j] = tmp;
    }
    
    //Clcok end time savesd
    //Calculates total time (end-start)
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    
    return SortStats{"Insertion Sort",
                    v.size(),
                    num_comps,
                    elapsed_cpu_time_sec};
}

template <typename T>
SortStats selection_sort(vector<T> &v){
    ulong num_comps = 0;
    clock_t start = clock();
    T temp;

    //if size of vector is 0 already sorted
    if(v.size()>=1)
    {
        //iterate through each element
        for (int i = 0; i < v.size() - 1; i++)
        {
            int vectMin = i;
            //loops through all the other elements after v[i]
            //when an element is less than element stored in vectmin we store the position
            for (int j = i + 1; j < v.size(); j++)
            {
                num_comps++;
                if(v[j] < v[vectMin])
                {
                    vectMin = j;
                }
            }
        // swap the element at v[i] and v[vectormin]
        temp = v[i];
        v[i] = v[vectMin];
        v[vectMin] = temp;
        }
    }
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Selection Sort",
                    v.size(),
                    num_comps,
                    elapsed_cpu_time_sec};
}
//Helper for mergeSort
//takes 2 sorted vectors and put them into 1 single sorted array
//used to merge the revursivly called sub vectors.
template <typename T>
int mergeSorting(vector<T>&left, vector<T>& right, vector<T>& vs)
{

    //setting size of left and right arrays
    int nL = left.size();
    int nR = right.size();

    //j tracks current index of left vector
    //k tracks current index of right vector
    //i is position of final vector
    //ret is the number of comparisons
    int i = 0, j = 0, k = 0, ret = 0;
;


    //Loop until we reach end of either left or right vector
    while (j < nL && k < nR) 
    {
        ret++; //<---------- number of comparisons incremented here

        //If current position of left vector less than current position of right vector, we put left vector element in finalvectors
        if (left[j] < right[k]) {
            vs[i] = left[j];
            //iterate left vector tracker
            j++;
        }
        //otherwise we move element from right vector into final vector
        //right[i]<=left[j]
        else {
            vs[i] = right[k];
            //iterate right tracker
            k++;
        }
        //incremenet position of final vector
        i++;
    }

    //Adding remaining elements from non empty vector to final vector 
    while (j < nL) {
        vs[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        vs[i] = right[k];
        k++; i++;
    }
    return ret;
}

//Main Merge sort algorithm that is recursivly called
template <typename T>
int sort(vector<T> &v){
    int ret = 0; // tracks the number of comparisons 
    
    // if the size of the vector is 1 or less, we do not need divide it
    if (v.size() <= 1) {
        return 0;
        }

    //position at which we divide the vector
    int mid = v.size() / 2;
    vector<T> left;
    vector<T> right;

    // moves all elements to left of v[j] in vector left
    for (size_t j = 0; j < mid;j++){
        left.push_back(v[j]);
    }
     // moves all elements to right of v[j] in vector left
    for (size_t j = 0; j < (v.size()) - mid; j++){
        right.push_back(v[mid + j]);
    }

    //recursively calls sort on the new left and right vectors until we have many vectors of 1 element
    //need to add number of comparisons for each recusive call so we add the returned values.   
    ret+=sort(left);
    ret+=sort(right);
    //once we have 1 element vecotrs mergesorting is continuously called
    //combines all the vectors into one sorted vector
    ret+=mergeSorting(left,right,v);
    return ret;
}

//main function that is called
//used to keep track of the clock and comparisons
//primary ease of use
template <typename T>
SortStats merge_sort(vector<T> &v){
    ulong num_comps = 0;
    clock_t start= clock();

    //num of comps is value returned from helper function
    num_comps = sort(v);
    
    clock_t end= clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return SortStats{"Merge Sort",
                    v.size(),
                    num_comps,
                    elapsed_cpu_time_sec};
}



//Helper Fuction for quicksort
//returns the  index of new partition for sub vectors
// elements left to partition is smaller than partition element
//element right to partition is bigger than partition element
template <typename T>
int Partition(vector<T> &v, int start, int end, ulong* comps){
	//sets pivot to last element of subvector
	int pivot = end;
	//swaping element index
    int j = start;
    //iterates through subvector
	for(int i=start;i<end;++i){
        (*comps)++; //<------------ comps incremented here
        
        //when any ith element is less than our pivot we swap i and j
        if(v[i]<v[pivot]){
			swap(v[i],v[j]);
            //increment swapping element
			++j;
		}
	}
    //swap the swapping element with pivot.
    // now all elements smaller than pivot is to the left, element bigger to the right
	swap(v[j],v[pivot]);
	return j;
}

//second helper for Quick sort
//main function used to recursively call itself to create new subvectors and partitions
template <typename T>
void quick_sort_main(vector<T> &v, int start, int end, ulong* comps){
    // stop when our start>= our end
    if(start<end){
        int p = Partition(v,start,end, comps);
        quick_sort_main(v,start,p-1, comps);
        quick_sort_main(v,p+1,end,comps);
    }
}

//main function that is called
//used to keep track of the clock and comparisons
//primary ease of use
template <typename T>
SortStats quick_sort(vector<T> &v){
    clock_t start = clock();
    ulong num_comps = 0;

    //pass address of num_comps to be iterated through helperfunctions
    quick_sort_main(v,0,v.size()-1,&num_comps);
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Quick Sort",
                    v.size(),
                    num_comps,
                    elapsed_cpu_time_sec};
}



//Shell sort sorting algorithm 
//Works by swapping elements that are x distance apart then slowly reducing the distance to continue swapping
template <typename T>
SortStats shell_sort(vector<T> &v){
    clock_t start = clock();
    ulong num_comps = 0;
    int n = v.size();

    for(int gap = n/2; gap>0;gap/=2){
         // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted 
        for(int i = gap;i<n;i++){
             // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            T temp = v[i];
            int j;
             // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            for(j=i;j>=gap && v[j-gap]>temp; j-=gap){
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
                    elapsed_cpu_time_sec};
}


//Iquicksort helper function
template <typename T>
void i_quick_sort_main(vector<T> &v, int start, int end, ulong* comps){
    if(start<end){
        //if the given vector is less than 25 elements we do insertion sort on the vector
        if(end - start < 25){
            int i,j;
            T tmp;
        //Insertion sort algorithm
            for(i=start;i<=end;i++)
            {
                j=i;
                tmp = v[i];
                (*comps)++;//<----- num_comps incremeneted here

                //for each element we move backwards in the vector
                //we insert the ith element to a posistion where it is greater than all elemenets before it
                while (j>0 && tmp<v[j-1])
                {
                    (*comps)++;
                    v[j]=v[j-1];
                    j--;
                }
                //insert ith element where we stopped.
                v[j] = tmp;
            }
            return;
        }
        
        //finds left and right subvectors and partition element. 
        // elements left of partition is < partition
        //elementsright of partition is >= partition
        int p = Partition(v,start,end, comps);

        //recursively call this function on left and right subvectors given partition p
        i_quick_sort_main(v,start,p-1, comps);
        i_quick_sort_main(v,p+1,end,comps);
    }
}
//Iquicksort sorting algorithm
//standard quicksort but we instead do insertion sort when vectors are below certain length
template <typename T>
SortStats iquick_sort(vector<T> &v){
    clock_t start = clock();
    ulong num_comps = 0;
    
    //calls the helper function to sort vector
    //calls with address of num_comps as parameter 
    i_quick_sort_main(v,0,v.size()-1,&num_comps);
    
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"IQuick Sort",
                    v.size(),
                    num_comps,
                    elapsed_cpu_time_sec};
}
//
// Returns a vector of n randomly chosen ints, each <= max and >= min.
//
vector<int> rand_vec(int n, int min, int max){
    vector<int> v;
    for(int i=0; i<n;i++){
        v.push_back(rand()%(max-min+1)+min);
    }
    return v;
}
