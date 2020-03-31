#include <iostream>
#include <cstddef>

using namespace std;

void error_msg(initializer_list<string> il)
{
    for(const auto &elem:il)
        cout<<elem<<" ";
    cout<<endl;
}

int main(int argc, char const *argv[])
{
    error_msg({"function X","abs","cdn"});

    error_msg({"da","www"});
    
    return 0;
}
