#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> vec{1,2,3,4,5};
    int sum = accumulate(vec.cbegin(),vec.cend(),0);
    cout<<sum<<endl;
    vector<double> vec2{1.2,3.4,5.6};
    cout<<accumulate(vec2.cbegin(),vec2.cend(),0.0)<<endl;
    return 0;
}
