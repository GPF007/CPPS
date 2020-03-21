#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(int argc, char const *argv[])
{
    int a;
    vector<int> v;
    while(cin>>a) v.push_back(a);
    cout<<"相邻两数的和："<<endl;
    for(vector<int>::size_type i=0;i<v.size();i+=2){
        int sum = v[i] + (i+1>v.size()?0:v[i+1]);
        cout<<sum<<endl;
    }
    
    cout<<"首尾两数的和："<<endl;
    typedef vector<int>::size_type st;
    for(st i=0,j=v.size();i<=j;++i,--j){
        int sum = v[i] + v[j];
        if(i==j) sum/=2;
        cout<<sum<<endl;
    }

    return 0;
}
