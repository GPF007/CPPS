#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main(int argc, char const *argv[])
{
    unordered_set<string> sym1;
    sym1.insert("hello");
    auto it = sym1.find("hello");
    const string *ps = &(*it);
    cout<<*ps<<endl;


    return 0;
}
