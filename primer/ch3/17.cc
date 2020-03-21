#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(int argc, char const *argv[])
{
    string s;
    vector<string> v;

    while(cin>>s){
        v.push_back(s);
    }
    cout<<"read done!"<<endl;

    for(auto &word: v){
        for(auto &c: word)
            c = toupper(c);
    }

    for(auto &word:v){
        cout<<word<<endl;
    }

    return 0;
}
