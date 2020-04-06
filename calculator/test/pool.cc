#include <iostream>
#include <memory>
#include <vector>

using namespace std;


template<typename T>
class Alloc
{
public:

    Alloc(size_t a): idx(a),sz(a),p_(nullptr){} 
    T* alloc();
    void free(T*);
    void clear();

    template<typename... Args>
    T* newElement(Args&&... args);

    ~Alloc() {clear();}



private:

    size_t idx,sz;
    T* p_;
    allocator<T> alloc_;
    vector<T*> vec;

};



template<typename T>
T* Alloc<T>::alloc(){
    if(idx >= sz){
        //需要新分配内存
        p_ = alloc_.allocate(sz);
        idx = 0;
        vec.push_back(p_);//保存分配的起始地址
    }
    return (p_ + (idx++));
}


template<typename T>
void Alloc<T>::clear(){
    for(auto p:vec){
        for(size_t i = 0;i<sz;i++){
           // if((p+i)!=nullptr)
                alloc_.destroy((p+i));
        }
        alloc_.deallocate(p,sz);
    }
}

template<typename T>
template<typename... Args>
T* Alloc<T>::newElement(Args&&... args)
{
    T* cur = alloc();
    alloc_.construct(cur,args...);
    return cur;

}



class Point{
public:

    Point(int xx, int yy):x(xx),y(yy){}

    int x,y;


};





int main(int argc, char const *argv[])
{
    /* code */
    static Alloc<Point> pointpool(10);

    auto p = pointpool.newElement(1,2);
    cout<<p->x<<", "<<p->y<<endl;

    allocator<string> a;
    auto beg = a.allocate(10);
    a.construct(beg,"hello");
    a.construct(beg+1,"world");
    a.construct(beg+3,"wd");
    cout<<*beg<<endl;
    cout<<*(beg+1)<<endl;
    cout<<*(beg+2)<<endl;
    cout<<*(beg+3)<<endl;

    //a.destroy(beg+100);

    

    return 0;
}
