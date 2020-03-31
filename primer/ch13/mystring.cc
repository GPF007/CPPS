
#include "mystring.h"
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

//uninitialized_copy(b,e,b2); 从迭代器b-e的输入范围拷贝元素到迭代其b2制定的未构造的原始内存中
//返回最后一个元素之后的位置
pair<char*,char*> String::alloc_n_copy(const char* b,const char* e){
    auto str = alloc.allocate(e-b);
    return {str, std::uninitialized_copy(b,e,str)};
}
void String::range_initializer(const char* first, const char* last){
    auto newstr = alloc_n_copy(first, last);
    elements = newstr.first;
    end = newstr.second;
}

void String::free(){
    if(elements){
        for_each(elements,end, [this](char &c){alloc.destroy(&c);});
        alloc.deallocate(elements, end-elements);
    }

}

//const char *s 表示const修饰指针指向的内容，内容不可变，即s可以指向别处，但不能够通过修改s来
//改变指向的内容
String::String(const char *s){
    char *sl = const_cast<char*>(s);
    while(*sl)
        ++sl;
    range_initializer(s,++sl);
    cout<<"Construct"<<endl;
}
String::String(const String& rhs){
    range_initializer(rhs.elements,rhs.end);
    cout<<"copy constructor"<<endl;
}

String::String(const String&& rhs){
    range_initializer(rhs.elements,rhs.end);
    cout<<"move constructor"<<endl;
}

String& String::operator=(const String& rhs){
    auto newstr = alloc_n_copy(rhs.elements,rhs.end);
    free();
    elements = newstr.first;
    end = newstr.second;
    cout<<"copy-assignment"<<endl; 
}

String::~String(){
    free();
}


char& String::operator[](int i){
    assert(i>=0 && i<size());
    return *(elements + i);
}
    
const char& String::operator[](int i) const
{
    assert(i>=0 && i<size());
    return *(elements + i);
}