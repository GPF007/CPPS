#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
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

//非模板的版本
string debug_rep(const string &s){
    return '"'+s +'"';
}

// convert the character pointers to string and call the string version of debug_rep
std::string debug_rep(char *p)
{
    return debug_rep(std::string(p));
}

std::string debug_rep(const char *p)
{
    return debug_rep(std::string(p));
}


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


template <typename... Args>
ostream &errorMsg(ostream &os, const Args&... rest)
{
    return print(os, debug_rep(rest)...); //这种调用形式表示在rest的每个参数都要调用debug_rep
}


int main(int argc, char const *argv[])
{
    string s("aaa");
    errorMsg(cout,1,2,3,4,"sss",s);
    return 0;
}
