#include <iostream>
#include <string>
using namespace std;

struct Sales_data{
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};


int main(int argc, char const *argv[])
{
    Sales_data sd1,sd2;
    double price = 0;
    cin>>sd1.bookNo>>sd1.units_sold>>price;
    sd1.revenue = sd1.units_sold*price;
    cout<<"sd1 revenue is :"<<sd1.revenue<<endl;
    
    return 0;
}
