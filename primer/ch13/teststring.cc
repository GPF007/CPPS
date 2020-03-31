#include "mystring.h"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    const char* s0 = "hello world";
    String s1(s0);
    String s2(s1);
    String s3 = s1;
    for(int i=0;i<s3.size();++i)
        cout<<s3[i]<<" ";
    cout<<endl;

    String s4(std::move(s1));
    cout<<s4.c_str()<<endl;

    return 0;
}
