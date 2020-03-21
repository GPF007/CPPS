#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char const *argv[])
{
    int i, &ri = i;
    i = 5; ri =10;
    cout<<"i:"<<i<<" ri:"<<ri<<endl;

    return 0;
}
