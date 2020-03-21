#include <iostream>
#include <iomanip>
using namespace std;

typedef double wages; //wages 是double的同义词
typedef wages base, *p; //base 是double的同义词，p 是double*

using INT = int;

typedef int *pint;


int main(int argc, char const *argv[])
{
    /* code */
    pint pa = new int(10);
    cout<<*pa<<endl;


    int a=3,b=4;
    decltype(a) c = a;
    decltype((b)) d =a; //双括号表示引用


    return 0;
}
