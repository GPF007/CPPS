#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

template <typename T>
ostream &print(ostream &os, const T &t)
{
    return os<<t; //包中最后一个元素之后不打印分割副
}

template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest)
{
    os<<t<<", ";
    return print(os,rest...);
}

template <typename T> 
string debug_rep(const T &t)
{
    ostringstream ret;
    ret <<t;
    return ret.str();
}

//打印指针的值
template <typename T> 
string debug_rep(T *p)
{
    ostringstream ret;
    ret<<"pointer: "<<p;
    if(p)
        ret<<" "<<debug_rep(*p);
    else
        ret <<" null pointer";
    return ret.str();
}


template <typename... Args>
ostream &errorMsg(ostream &os, const Args&... rest)
{
    return print(os, debug_rep(rest)...); //这种调用形式表示在rest的每个参数都要调用debug_rep
}


int main(int argc, char const *argv[])
{
    int i =7;
    string s = "hello";
    print(cout,i,s,42);
    cout<<endl;
    return 0;
}
