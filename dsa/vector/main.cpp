#include <iostream>
#include <cstdio>
#include "vector.h"
using namespace std;

//function object
template <typename T>
struct Increase{
    virtual void operator()(T& e){e++;}
};

void show_vector(Vector<int>& v){
    cout<<"This is vector elements:"<<endl;
    for(int i=0;i<v.size();i++){
        printf("v[%d] = %d, size=%d, capacity=%d\n",
            i,v[i],v.size(),v.capacity());
    }
}





int main(int argc, char const *argv[])
{
    cout<<"Hello world"<<endl;
    int a[3]={1,2,3};
    Vector<int> v1;
    Vector<int> v2(a,3);
    //cout<<"v2[2]"<<v2[3]<<endl;
    v2.insert(0,100);
    auto inc=Increase<int>();
    v2.traverse(inc);

    for(int i=0;i<v2.size();i++){
        printf("a[%d] = %d, size=%d, capacity=%d\n",
            i,v2[i],v2.size(),v2.capacity());
    }
    v2.remove(0);
    int i=v2.search(5);
    show_vector(v2);
    v2.insert(i,5);
    show_vector(v2);

    int b[4]={4,3,2,1};
    Vector<int> v3(b,4);
    v3.sort();
    show_vector(v3);


    //cout<<"traverse:"<<endl;


    return 0;
}


