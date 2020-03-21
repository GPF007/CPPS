#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    string s;
    cin>>s;
    for(auto &ch:s)
        ch = 'X';
    cout<<s<<endl;
    return 0;
}
