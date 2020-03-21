#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    string s1,s2;
    while(cin >> s1 >>s2){
        if(s1 != s2)
            cout<< (s1>s2?s1:s2)<<endl;
    }
    return 0;
}
