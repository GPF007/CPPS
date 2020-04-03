#include <iostream>
#include <memory>
#include <vector>



using namespace std;




template<typename T>
class Alloc
{

    

public:

    Alloc(int a): sz(a),idx(a){} 

    template<typename... Args>
    T* newElement(Args&&... args);



private:

    void check_alloc();

    int sz;

    T* cur;
    int idx;
    allocator<T> alloc_;

    vector<T*> vec;

};



template<typename T>
template<typename... Args>
T* Alloc<T>::newElement(Args&&... args)
{
    check_alloc();
    alloc_.construct(cur+idx,args...);
    vec.push_back(cur+idx);
    ++idx;
    return cur+(idx-1);

}
template<typename T>
void Alloc<T>::check_alloc()
{
    if(idx<sz) 
        return;

    cout<<"alloc memory !"<<endl;
    idx = 0;
    cur = alloc_.allocate(sz);
}



int main(int argc, char const *argv[])
{
    /* code */
    int n =10;
    allocator<string> alloc;
    string* const p = alloc.allocate(n);
    auto q = p;
    //alloc.construct(q++);
    alloc.construct(p+1,"aa");
    alloc.construct(p+2,"bb");
    alloc.construct(p+3,"cc");
    cout<<p[1]<<endl;
    cout<<p[2]<<endl;
    cout<<p[3]<<endl;

    
    Alloc<string> mem(7);
    string *ps = mem.newElement("hello");
    for(int i=0;i<10;i++)
        mem.newElement("hell0");
    cout<<*ps<<endl;
    

    return 0;
}
