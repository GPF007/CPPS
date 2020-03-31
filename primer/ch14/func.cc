#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct absInt{
    int operator()(int val) const{
        return val<0?-val:val;
    }
};

int add(int i,int j) {return i+j;}

auto mod = [](int i,int j) {return i%j;};

struct divide{
    int operator()(int a,int b){
        return a/b;
    }
};

int main(int argc, char const *argv[])
{

    using fun = function<int(int,int)>;
    fun f1=add;
    fun f2= divide();
    fun f3= mod;

    cout<<f1(4,2)<<endl;
    cout<<f2(4,2)<<endl;
    cout<<f3(10,3)<<endl;
    return 0;
}
