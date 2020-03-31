#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> vec{"12322222","1234567","sad"};
    int sz = 6;
    int count = count_if(vec.begin(), vec.end(),
                        [sz](string s) {return s.size()>=6;});

    cout<<count<<endl;

    return 0;
}
