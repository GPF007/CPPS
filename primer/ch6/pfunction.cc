#include <iostream>
#include <vector>

using namespace std;




int func(int a,int b);
using pFunc1 = decltype(func)*;
typedef decltype(func) *pFunc2;
using pFunc3 = int(*)(int a,int b);
using pFunc4 = int(int a,int b);
typedef int(*pFunc5)(int a, int b);
using pFunc6 = decltype(func);

vector<pFunc1> vec1;
vector<pFunc2> vec2;
vector<pFunc3> vec3;
vector<pFunc4*> vec4;
vector<pFunc5> vec5;
vector<pFunc6*> vec6;

int add(int a,int b) {return a+b;}
int sub(int a,int b) {return a-b;}
int mul(int a, int b) {return a*b;}
int divv(int a,int b) {return b!=0?a/b:0;}



int main(int argc, char const *argv[])
{
    vector<pFunc1> vec{add,sub,mul,divv};

    for(auto f:vec){
       // cout<<f<<endl;
        cout<<f(4,5)<<endl;
    }

    return 0;
}
