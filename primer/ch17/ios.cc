#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(int argc, char const *argv[])
{
    cout<<boolalpha;
    cout<<true<<endl;
    cout<<false<<endl;
    cout<<noboolalpha;

    cout<<showbase;
    cout<<"default: "<<20<<" "<<1024<<endl;
    cout<<"octal: "<<oct<<20<<" "<<1024<<endl;
    cout<<"hex: "<<hex<<20<<" "<<1024<<endl;
    cout<<"decimal: "<<dec<<20<<" "<<1024<<endl;
    cout<<noshowbase;

    cout<<"Precision: "<<cout.precision()
        <<", Value: "<<sqrt(2.0)<<endl;
    cout.precision(12);
    cout<<"Precision: "<<cout.precision()
        <<", Value: "<<sqrt(2.0)<<endl;
    cout<<setprecision(3);
    cout<<"Precision: "<<cout.precision()
        <<", Value: "<<sqrt(2.0)<<endl;

    return 0;
}
