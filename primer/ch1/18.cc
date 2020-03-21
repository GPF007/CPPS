#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char const *argv[])
{
    int i = 10;
    int *pi = &i;
    int &ri = i;

    cout<<"i初值为"<<i<<endl;

    *pi = 11;
    cout<<"根据指针修改值 i = "<<i<<endl;

    ri = 12;
    cout<<"根据引用修改值 i = "<<i<<endl;


    
    return 0;
}
