#include <iostream>
#include <initializer_list>

using namespace std;

int sum(initializer_list<int> il){
    int sum = 0;
    for(auto &elem:il) sum+=elem;
    return sum;
}


int main(int argc, char const *argv[])
{
    auto it = {1,2,3,4,5};
    cout<<sum(it)<<endl;
    
    return 0;
}
