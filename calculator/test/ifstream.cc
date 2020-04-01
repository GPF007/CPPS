#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream in;
    in.open("teststr.cc");
    string s;
    int ch;
    while((ch = in.get())!=EOF)
        cout<<char(ch);
    return 0;
}
