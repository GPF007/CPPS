#include <iostream>
#include <vector>

using namespace std;

typedef vector<int>::iterator Iter;

Iter find(Iter begin, Iter endd, int target){
    while(begin!=endd){
        if(*begin == target) return begin;
        ++begin;
    }
    return endd;

}

int main(int argc, char const *argv[])
{

    vector<int> vec{1,2,3,4,5};
    Iter ans = find(vec.begin(),vec.end(),3);
    if(ans == vec.end())
        cout<<"not found"<<endl;
    else
        cout<<*ans<<endl;

    return 0;
}
