#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <cstring>
using namespace std;


template<typename T>
int compare(const T&, const T&);

/*特例化哦*/
template<>
int compare(const char* const &p1, const char* const &p2)
{
    return strcmp(p1,p2);
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

