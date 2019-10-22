#include "vector.h"


/*
//create a new Vector with a vecotr A
template <typename T>
void Vector<T>::copyFrom(T const* A,Rank lo,Rank hi){
    _capacity=2*(hi-lo);
    _elem=new T[_capacity];
    _size=0;

    while(lo<hi){
        _elem[_size++]=A[lo++];
    }

} 
*/

/*

//Overload = operator
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const &V){
    if (_elem) delete []_elem;
    copyFrom(V._elem,0,V.size());

    return *this;
}
*/

//Overload '[]' operator
