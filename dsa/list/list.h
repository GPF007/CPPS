#include <cstdlib>


typedef int Rank;

/*
    This part is Node struct

*/
#define Posi(T) ListNode<T>*

template <typename T>
struct ListNode{
    T data;
    Posi(T) pred; //the previous node of current
    Posi(T) succ;//the next node of current


    //Constructe function
    ListNode(){}
    ListNode(T e,Posi(T) p=NULL,Posi(T) s=NULL)
    :data(e),pred(p),succ(s){}

    //Insert function
    Posi(T) insertAsPred(T const& e){
        Posi(T) newNode=new ListNode<T>(e,pred,this);
        pred->succ=newNode;
        pred=newNode;    
        return newNode;
    }
    Posi(T) insertAsSucc(T const& e){
        Posi(T) newNode=new ListNode<T>(e,this,succ);
        succ->pred=newNode;
        succ=newNode;
        return newNode;
    }

};







/*
    This part is List class
    
*/

template <typename T>
class List{
private:
    int _size;//size of nodes
    Posi(T) header;                   
    Posi(T) trailer;


protected:

    void init();
    int clear();
    void copyNodes(Posi(T) p,int n);//copy from node p to p+n [p,p+n]
    void merge(Posi(T)&, int, List<T>&, Posi(T), int);
    void mergeSort(Posi(T)&, int); //merge sort
    void selectionSort(Posi(T),int); //select sort p to p+n
    void insertionSort(Posi(T),int); //insert sort p to p+n


public:

    //Construct functions
    List() {init();}
    List(List<T> const& L); //copy L to this list
    List(List<T> const& L,Rank r,int n);
    List(Posi(T) P,int n); //copy itself
    //Desctruct function
    ~List();


    //Read only interface
    Rank size() const {return _size;}
    bool empty() const { return _size <=0;}
    T &operator[](Rank r) const; //overload '[]' to read by rank
    Posi(T) first() const{return header->succ;}
    Posi(T) last() const {return trailer->pred;}
    bool valid(Posi(T) p){return p && (trailer!=p) && (header!=p);}
     //judge whether p is accessable to out
    int disordered() const; //whether is sorted
    //unordered
    Posi(T) find(T const& e) const {return find(e,_size,trailer);}
    Posi(T) find(T const& e,int n,Posi(T) p);//find e before p with n nodes
    //ordered
    Posi(T) search(T const& e) const {return search(e,_size,trailer);}
    Posi(T) search(T const& e,int n,Posi(T) p);//find e before p with n nodes

    Posi(T) selectMax(Posi(T) p, int n);//select max e from p+1 to p+n
    Posi(T) selectMax(){return selectMax(header->succ,_size);}
    
    //Writeable interface
    Posi(T) insertAsFirst(T const& e); //insert e as first
    Posi(T) insertAsLast(T const& e); //insert e as last
    Posi(T) insertBefore(Posi(T) p, T const& e);
    Posi(T) insertAfter(Posi(T) p, T const& e);
    T remove(Posi(T) p);//remove node p and return its value
    void merge(List<T>& L){merge(first(),_size,L,L.first(),L.size());}
    void sort(Posi(T) p,int n);//sort p to p+n
    void sort(){sort(first(),_size);}
    int deduplicate();//unordered unique
    int uniquify(); //ordered unique
    void reverse();
    //traverse
    void traverse(void (*)(T&));
    template <typename VST>
    void traverse(VST&);


};

/*
    Protect function implements
*/
template <typename T>
void List<T>::init(){
    header=new ListNode<T>;
    trailer=new ListNode<T>;
    header->succ=trailer;
    trailer->pred=header;
    _size=0;
}

//clear the list
template <typename T>
int  List<T>::clear(){
    int old_size=_size;
    while(_size > 0){
        remove(header->succ);
    }

    return old_size;
}

//copy node to current list
template <typename T>
void List<T>::copyNodes(Posi(T) p,int n){
    init();
    while(n-- > 0){
        insertAsLast(p->data);
        p=p->succ;
    }
}

//Insert sort
template <typename T>
void List<T>::insertionSort(Posi(T) p,int n){
    for(int r=0;r<n;r++){
        insertAfter(search(p->data,r,p),p->data);
        p=p->succ;
        remove(p->pred);
    }
}

//Selection sort
template <typename T>
void List<T>::selectionSort(Posi(T) p,int n){
    Posi(T) head=p->pred;
    Posi(T) tail = p;
    for(int i=0;i<n;i++){
        tail=tail->succ;
    }
    while((1<n)){
        Posi(T) max=selectMax(head->succ,n);
        insertBefore(tail,remove(max));
        tail=tail->pred;
        n--;
    }   
}

//select max node
template <typename T>
Posi(T) List<T>::selectMax(Posi(T) p,int n){
    Posi(T) max=p;
    for(Posi(T) cur=p;1<n;n--){
        cur=cur->succ;
        if(cur->data >= max->data)
            max=cur;
    }

    return max;
}

//merge sort
template <typename T>
void List<T>::mergeSort(Posi(T)& p, int n){
    if(n<2) return;
    int m = n>>1; //m is mid
    Posi(T) q=p;
    for(int i=0;i<m;i++)
        q=q->succ;
    
    mergeSort(p,m);
    mergeSort(q,n-m);
    merge(p,m,*this,q,n-m);
}

template <typename T>
void List<T>::merge(Posi(T)& p, int n, List<T>& L, Posi(T) q, int m){
    Posi(T) pp=p->pred;
    while(0<m){
        if((0<n) && (p->data<=q->data)){
            if(q==(p=p->succ))
                break;
            n--;
        }else{
            insertBefore(p,L.remove((q=q->succ)->pred));
            m--;
        }
    }

    p=pp->succ;
}


/*
    Public functions
*/

//Cosntruct functions
template <typename T>
List<T>::List(List<T> const& L){
    copyNodes(L.first(),L.size());
}

template <typename T>
List<T>::List(List<T> const& L,Rank r,int n){
    copyNodes(L[r],n);
}

template <typename T>
List<T>::List(Posi(T) p,int n){
    copyNodes(p,n);
}

//Destruct functions
template <typename T>
List<T>::~List(){
    clear();
    delete header;
    delete trailer;
}


//overlaod []
template <typename T>
T& List<T>::operator[](Rank r) const{
    Posi(T) p=first();
    while(r-- > 0){
        p=p->succ;
    }
    return p->data;
}

//find e before p with n nodes
template <typename T>
Posi(T) List<T>::find(T const& e,int n,Posi(T) p){
    while(n-- > 0){
        p=p->pred;
        if(p->data == e)
            return p;
    }
    return NULL;
}

//insert as first
template <typename T>
Posi(T) List<T>::insertAsFirst(T const& e){
    _size++;
    return header->insertAsSucc(e);
}
//inser tas last
template <typename T>
Posi(T) List<T>::insertAsLast(T const& e){
    _size++;
    return trailer->insertAsPred(e);
}
//insert before p
template <typename T>
Posi(T) List<T>::insertBefore(Posi(T) p, T const& e){
    _size++;
    return p->insertAsPred(e);
}
//insert after p
template <typename T>
Posi(T) List<T>::insertAfter(Posi(T) p, T const& e){
    _size++;
    return p->insertAsSucc(e);
}

//remove node p and return its value
template <typename T>
T List<T>::remove(Posi(T) p){
    T data=p->data;
    p->pred->succ=p->succ;
    p->succ->pred=p->pred;
    delete p;
    _size--;
    return data;
}

//unordered unique
template <typename T>
int List<T>::deduplicate(){
    if(_size<2) return 0;
    int old_size=_size;
    Rank r=0;
    Posi(T) p=first();
    while(p!=trailer){
        Posi(T) q=find(p->data,r,p);
        (q==NULL)?(r++):(remove(q));
        p=p->succ;
    }
    return old_size - _size;
}

//ordered unique
template <typename T>
int List<T>::uniquify(){
    if(_size<2) return 0;
    int old_size=_size;
    Posi(T) p=header;
    Posi(T) q=p->succ;
    while(q!=trailer){
        if(p->data == q->data){
            remove(q);
            q=p;
        }

        p=q;
        q=q->succ;
    }

    return old_size - _size;

}

//ordered search
template <typename T>
Posi(T) List<T>::search(T const& e,int n,Posi(T) p){
    while(n-- >= 0){
        p=p->pred;
        if(p->data <= e)
            break;
    }
    return p;
}

//sort
template <typename T>
void List<T>::sort(Posi(T) p,int n){
    switch (rand() % 3)
    {
        case 1: insertionSort(p,n); break;
        case 2: selectionSort(p,n); break;
        default: mergeSort(p,n);break;
    }
}

//revere the list
template <typename T>
void List<T>::reverse(){
    if(_size<2) return;

    Posi(T) p=first();
    Posi(T) q;
    p=p->succ;
    while(trailer != p){
        q=p;
        p=p->succ;
        T e=remove(q);
        insertAsFirst(e);
    }
}






//traverse
template <typename T>
void List<T>::traverse(void (*visit)(T&)){
    Posi(T) p=first();
    int n=_size;
    while(n-- > 0){
        visit(p->data);
        p=p->succ;
    }
}
template <typename T> template <typename VST>
void List<T>::traverse(VST& visit){
    Posi(T) p=first();
    int n=_size;
    while(n-- > 0){
        visit(p->data);
        p=p->succ;
    }
}