#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    string s,res;
    while(cin>>s){
        res = res +" " + s;
    }
    cout<< res.substr(1,res.size()-1)<<endl;
    
    return 0;
}
