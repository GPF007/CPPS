#include <iostream>
#include <cstddef>

using namespace std;

void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}


int main(int argc, char const *argv[])
{
    int a =10,b=42;
    cout<<"before swap:"<<a<<" "<<b<<endl;
    swap(a,b);
    cout<<"after swap:"<<a<<" "<<b<<endl;

    
    
    return 0;
}
