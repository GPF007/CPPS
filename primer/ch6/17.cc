#include <iostream>
#include <cstddef>
#include <string>
#include <cctype>

using namespace std;

bool hasUpper(const string &s){
    for(auto &c:s){
        if(isupper(c))
            return true;
    }
    return false;
}

void toLower(string &s){
    for(auto &c:s){
        c = tolower(c);
    }
}

int main(int argc, char const *argv[])
{
    string s = "Hello World!";
    cout<<hasUpper(s)<<endl;
    toLower(s);
    cout<<s<<endl;
    return 0;
}
