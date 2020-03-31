#include <iostream>
#include <cstddef>

using namespace std;


size_t count_calls()
{
    static size_t ctr = -1;
    return ++ctr;
}
int main()
{
    for(size_t i =0;i!=10;++i){
        cout<<"Call times: "<<i<<endl;
        cout<<count_calls()<<endl;
    }
    return 0;
}