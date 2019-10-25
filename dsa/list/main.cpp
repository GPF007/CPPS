#include "list.h"
#include <iostream>
using namespace std;


//function object
template <typename T>
struct Print{
    virtual void operator()(T& e){
        cout<<e<<"-->";
    }
};

/*
void show_vector(Vector<int>& v){
    cout<<"This is vector elements:"<<endl;
    for(int i=0;i<v.size();i++){
        printf("v[%d] = %d, size=%d, capacity=%d\n",
            i,v[i],v.size(),v.capacity());
    }
}
*/


int main(int argc, char const *argv[])
{
    cout<<"Hello world!"<<endl;
    List<int> a;
    a.insertAsLast(1);
    a.insertAsLast(2);
    a.insertAsLast(4);
    a.insertAsLast(3);

    auto prin=Print<int>();
    cout<<a.size()<<endl;
    a.traverse(prin);
    a.sort();
    cout<<endl;
    a.traverse(prin);
    cout<<endl;
    a.reverse();
    a.traverse(prin);
    cout<<endl;
    return 0;
}
