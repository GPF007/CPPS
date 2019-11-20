#include <iostream>
#include "matchs.h"

using namespace std;


int main(int argc, char const *argv[])
{
    cout<<"Hello world!"<<endl;
    const char *p="we";
    const char *t="hello";
    int pos = brute_match(p,t);
    cout<<pos<<endl;

    cout<<"KMP match:"<<endl;
    cout<<kmp_match(p,t)<<endl;
    return 0;
}