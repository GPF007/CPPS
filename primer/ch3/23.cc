#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> v{1,2,3,4};
    for(auto it = v.begin();it!=v.end();++it)
        (*it)*=2;
    for(auto &i:v){
        cout<<i<<" ";
    }
    return 0;
}
