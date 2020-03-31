#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

bool ge5(string s){
    return s.size()>=5;
}

int main(int argc, char const *argv[])
{
    vector<string> vec{"hello","my","word","asdasda","fffxxxxxxxk"};
    auto part_iter = partition(vec.begin(),vec.end(),ge5);
    auto it = vec.begin();
    while(it!=part_iter){
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
    return 0;
}
