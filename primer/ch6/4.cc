#include <iostream>

using namespace std;

int fact(int n){
    if(n==0 || n==1)
        return 1;
    return n*fact(n-1);
}


int main(int argc, char const *argv[])
{
    int a;
    while(cin>>a){
        cout<<fact(a)<<endl;
    }

    return 0;
}
