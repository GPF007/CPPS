#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char const *argv[])
{
    unsigned u = 10, u2=42;
    cout<< u2 -u<<endl; //32
    cout<< u-u2 <<endl; //ffff ffe0


    int i=10, i2 =42;
    cout<<i2-i<<endl;
    cout<<i - i2<<endl;
    cout<<i-u <<endl;
    cout<<u-i<<endl;

    return 0;
}
