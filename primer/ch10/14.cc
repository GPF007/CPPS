#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    auto sum = [](int a,int b)->int {return a+b;};

    cout<<sum(3,4)<<endl;
    return 0;
}
