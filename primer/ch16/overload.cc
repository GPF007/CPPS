#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

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

int main(int argc, char const *argv[])
{
    string s("hello");
    string *ps = new string("hellow");
    cout<<debug_rep(s)<<endl;
    cout<<debug_rep(&s)<<endl;
    //cout<<debug_rep(ps)<<endl;
    return 0;
}
