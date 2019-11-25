#include <iostream>

using namespace std;

template <typename T>
int partition1(T* A,int lo,int hi);


template <typename T>
void quickSort(T* A,int lo, int hi){
    if(hi - lo<2) return;
    int mi = partition1(A,lo,hi-1);
    quickSort(A,lo,mi);
    quickSort(A,mi+1,hi);
}

// partition version 1
template <typename T>
int partition1(T* A,int lo,int hi){
    //swap pivot to the lo 
    swap(A[lo],A[lo+rand()%(hi-lo+1)]);
    T pivot = A[lo];

    while(lo<hi){
        while((lo<hi) && (pivot <= A[hi]))
            hi--;
        A[lo] = A[hi];
        while((lo<hi) && (A[lo] <= pivot))
            lo++;
        A[hi]=A[lo];
    }

    A[lo]=pivot;

    return lo;
}

// partition version 2
//prefer to swap than expand
template <typename T>
int partition2(T* A,int lo,int hi){
    //swap pivot to the lo 
    swap(A[lo],A[lo+rand()%(hi-lo+1)]);
    T pivot = A[lo];

    while(lo<hi){
        while(lo<hi){
            if(pivot < A[hi])
                hi--;
            else{
                A[lo++]=A[hi];
                break;
            }
        }
        while(lo<hi){
            if(pivot > A[hi])
                lo++;
            else{
                A[hi--]=A[lo];
                break;
            }
        }
    }

    A[lo]=pivot;
    return lo;
}

//find the major element if exist
template <typename T>
T majCandidate (T* A,int n){
    T maj;
    
    for(int c = 0,i=0;i<n;i++){
        if(c==0){
            maj = A[i];
            c=1;
        }else
            maj == A[i]?c++:c--;
    }

    return maj;
}

/*find the top K element in O(N)*/
template <typename T>
void quickSelect(T* A,int k,int n){
    for(int lo = 0,hi=n-1;lo<hi;){
        int i=lo,j=hi;
        T pivot = A[lo];

        while(i<j){
            while((i<j) && (pivot<=A[j]))
                j--;
            A[i]=A[j];
            while((i<j) && (A[i] <= pivot))
                i++;
            A[j]=A[i];
        }
        A[i] = pivot;
        if(k<=i) hi = i - 1;
        if(i<=k) lo = i + 1;
    }
    //A[k] is the target
    return A[k];
}