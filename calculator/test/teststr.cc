#include <iostream>
#include <unordered_map>

using namespace std;


std::unordered_map<char,std::string> table{
    {'+',"+"},
    {'-',"-"},
    {'*',"*"},
    {'/',"/"},
    {'(',"("},
    {')',")"},
};

int main(int argc, char const *argv[])
{
    int i = '3';
    string s;
    s.append(1,char(i));
    cout<<s<<endl;
    cout<<table['+']<<endl;

    return 0;
}
