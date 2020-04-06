#pragma once
#include <memory>
#include <vector>

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

    //~Alloc() {clear();}



private:

    size_t idx,sz;
    T* p_;
    std::allocator<T> alloc_;
    std::vector<T*> vec;

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