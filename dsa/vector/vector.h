
/*
    This is a template of vector
*/

#include <cassert>
#include <cstdlib>

typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T>
class Vector{
protected:
    /*elements*/
    Rank _size;
    int _capacity;
    T* _elem;

    //all help function 
    void copyFrom(T const*A,Rank lo,Rank hi);
    void expand();
    void shrink();
    bool bubble(Rank lo,Rank hi);
    void bubbleSort(Rank lo,Rank hi);
    Rank max(Rank lo,Rank hi);
    void selectSort(Rank lo,Rank hi);
    void merge(Rank lo,Rank mi,Rank hi);
    void mergeSort(Rank lo,Rank hi);
    Rank partition(Rank lo,Rank hi);
    void quickSort(Rank lo,Rank hi);
    void heapSort(Rank lo,Rank hi);



public:
    //Construct function
    Vector(int c=DEFAULT_CAPACITY,int s=0,T v=0)
    {
        _elem=new T[_capacity=c];
        for(_size=0;_size<s;_elem[_size++]=v);
    }
    Vector(T const* A,Rank lo,Rank hi){copyFrom(A,lo,hi);}
    Vector(T const* A,Rank n){copyFrom(A,0,n);}
    Vector(Vector<T> const &V,Rank lo,Rank hi){copyFrom(V._elem,lo,hi);}
    Vector(Vector<T> const &V){copyFrom(V._elem,0,V._size);}

    //Desctruct function
    ~Vector(){delete [] _elem;}

    //Operation overload
    Vector& operator=(Vector<T> const &v); //=
    T& operator[](Rank r); //[]

    /*Public interface*/
    //Read only ones
    Rank size() const {return _size;}
    Rank capacity() const {return _capacity;}
    bool empty() const {return !_size;}
    int disordered() const; //whether is ordered
    Rank find(T const& e) const{return find(e,0,_size);}//find elemen e; return index
    Rank find(T const& e,Rank lo,Rank hi) const;//with range
    Rank search(T const& e) const; //find ordered vetor(binary search)
    Rank search(T const& e,Rank lo,Rank hi) const;

    //Writeable ones
    T remove(Rank r);//delete rth elemetn
    int remove(Rank lo,Rank hi);
    Rank insert(Rank r,T const& e);
    Rank insert(T const& e){return insert(_size,e);}//default insert to end
    void sort(Rank lo,Rank hi);//sort [lo,hi)
    void sort(){sort(0,_size);}
    void unsort(Rank lo,Rank hi);
    void unsort(){unsort(0,_size);}
    int dedulicate();//unordered unique
    int uniquify();//ordered unique
    //traverse 
    void traverse(void (*)(T&));//use function pointer
    template <typename VST> void traverse(VST&); //use function object

    //static function
    static Rank binSearch(T* A,T const& e,Rank lo,Rank hi);
    static void swap(T& t1,T& t2){T tmp=t1;t1=t2;t2=tmp;}


};

/*
    Protected functions:
    These functions are help functions.
*/
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

//Expand the capacity
template <typename T>
void Vector<T>::expand(){
    if(_size<_capacity) return;
    if(_capacity < DEFAULT_CAPACITY)
        _capacity=DEFAULT_CAPACITY;//more than default capality
    
    _capacity*=2;
    T* old_elem=_elem;
    _elem=new T[_capacity];
    for(int i=0;i<_size;i++)
        _elem[i]=old_elem[i];
    //copy old to new and delete old
    delete [] old_elem;
}

//Shrink the capacity
template <typename T>
void Vector<T>::shrink(){
    if(_capacity < DEFAULT_CAPACITY/2) return;

    if(_size<<2 > _capacity) return;//%25 is limit
    T* old_elem=_elem;
    _elem=new T[_capacity>>1];//capacity decrease half
    for(int i=0;i<_size;i++)
        _elem[i]=old_elem[i];
    delete [] old_elem;
}

//bubble sort
template <typename T>
bool Vector<T>::bubble(Rank lo,Rank hi){
    bool sorted = true;
    while(++lo<hi){
        if(_elem[lo-1]>_elem[lo]){
            sorted=false;
            swap(_elem[lo-1],_elem[lo]);
        }
    }
    return sorted;
}
template <typename T>
void Vector<T>::bubbleSort(Rank lo,Rank hi){
    while(!bubble(lo,hi--));
}

template <typename T>
void Vector<T>::merge(Rank lo,Rank mi,Rank hi){
    T* A=_elem + lo;
    int lb=mi-lo;
    T* B= new T[lb];
    for(Rank i=0;i<lb;i++)
        B[i]=A[i];
    
    int lc=hi-mi;
    T *C=_elem+mi;
    
    for(Rank i=0,j=0,k=0;(j<lb) || (k<lc);){
        if((j<lb) && (!(k<lc) || (B[j]<=C[k]))) //B[j] is less
            A[i++]=B[j++];
        if((k<lc) && (!(j<lb) || (C[k] < B[j])))
            A[i++]=C[k++];
    }

    // a bettor one;when B is out of range then exit;
    /*
    for(Rank i=0,j=0,k=0;j<lb;){
        if((!(k<lc) || (B[j]<=C[k]))) //B[j] is less
            A[i++]=B[j++];
        if((k<lc) && ((C[k] < B[j])))
            A[i++]=C[k++];
    }
    */
    
    delete [] B;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo,Rank hi){
    if (hi-lo <2) return;
    int mi=(lo+hi)/2;
    mergeSort(lo,mi);
    mergeSort(mi,hi);
    merge(lo,mi,hi);
}


/*
    Public functions:
    These ars functions User can access

*/


//Overload = operator
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const &V){
    if (_elem) delete []_elem;
    copyFrom(V._elem,0,V.size());

    return *this;
}

//Overload '[]' operator
template <typename T>
T& Vector<T>::operator[](Rank r){
    assert(r>=0 && r<_size);
    return _elem[r];
}

//insert element e
template <typename T>
Rank Vector<T>::insert(Rank r,T const& e){
    expand();
    for(int i=_size;i>r;i--)
        _elem[i]=_elem[i-1];
    _elem[r]=e;
    _size++;

    return r;

}

//remove range [lo,hi),return removed length
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi){
    if(lo==hi) return 0;
    while(hi<_size){
        _elem[lo++]=_elem[hi++];
    }

    _size=lo;
    shrink();
    return (hi-lo);
}

//remove element at rank r
template <typename T>
T Vector<T>::remove(Rank r){
    T e=_elem[r];
    remove(r,r+1);
    return e;
}

//find element e in unordered vector
template <typename T>
Rank Vector<T>::find(T const& e,Rank lo,Rank hi) const{
    while((lo<hi--) && (e!=_elem[hi]));
    return hi;
}

//unique in unordered vector
template <typename T>
int Vector<T>::dedulicate(){
    int oldSize=_size;
    Rank i=1;
    while(i<_size){
        if(find(_elem[i],0,i)<0)
            i++;
        else
            remove(i);
    }

    return oldSize-_size;
}

//unique in ordered vector
template <typename T>
int Vector<T>::uniquify(){
    Rank i=0,j=0;

    while(++j<_size){
        if(_elem[i]!=_elem[j])
            _elem[i++]=_elem[j];
    }
    _size=++i;
    shrink();
    return j-i;
}

//traverse 
template <typename T>
void Vector<T>::traverse(void (*visit)(T&)){
    for(int i=0;i<_size;i++){
        visit(_elem[i]);
    }
}
template <typename T> template <typename VST> 
void Vector<T>::traverse(VST& visit){
    for(int i=0;i<_size;i++){
        visit(_elem[i]);
    }
}

//search element e from ordered vector
template <typename T>
Rank Vector<T>::search(T const& e,Rank lo,Rank hi) const{
    return binSearch(_elem,e,lo,hi);
}

//search element e from ordered vector
template <typename T>
Rank Vector<T>::search(T const& e) const{
    return binSearch(_elem,e,0,_size);
}

template <typename T>
void Vector<T>::sort(Rank lo,Rank hi){
    switch(rand() % 5){
        case 1:bubbleSort(lo,hi);break;
        case 2:mergeSort(lo,hi);
        default:bubbleSort(lo,hi);break;
    }
}




/*static functions*/
template <typename T>
Rank Vector<T>::binSearch(T* A,T const& e,Rank lo,Rank hi){
    while(lo<hi){
        Rank mid=(lo+hi)/2;
        if(e<A[mid])
            hi=mid;
        else
            lo=mid+1;
    }

    return --lo;
    
}

