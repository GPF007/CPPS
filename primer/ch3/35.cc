#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(int argc, char const *argv[])
{
    int ia[] = {2,4,5,6};
    for(int *p=begin(ia);p!=end(ia);++p)
        *p=0;

    for (auto ptr = ia; ptr != ia + 4; ++ptr) 
        *ptr = 0;
    
    return 0;
}
