#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> vec{1,2,3,4};
    cout<<"origin vector:"<<endl;
    for(auto &i: vec){
        cout<<i<<" ";
        i = (i&0x1)?i*2:i;
    }

    cout<<"\nafter convention:"<<endl;
    for(auto &i:vec) cout<<i<<" ";

    size_t a;
    
    return 0;
}
