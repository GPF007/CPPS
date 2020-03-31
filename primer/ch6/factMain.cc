#include <iostream>
#include "chapter6.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int a;
    while(cin>>a){
        cout<<fact(a)<<endl;
    }

    return 0;
}