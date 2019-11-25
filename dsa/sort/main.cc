#include <iostream>
#include <cstdlib>
#include "sort.h"

using namespace std;

#define N 10

int main(int argc, char const *argv[])
{
    int* A = new int[N];
    for(int i=0;i<N;i++){
        A[i] = rand()%N;
    }
    for(int i=0;i<N;i++)
        cout<<A[i]<<" ";
    cout<<endl;

    quickSort(A,0,N);
    cout<<"after sorting: "<<endl;
    for(int i=0;i<N;i++)
        cout<<A[i]<<" ";
    cout<<endl;
    return 0;
}
