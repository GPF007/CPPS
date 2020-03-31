#include <iostream>
#include <vector>

using namespace std;

typedef vector<int>::iterator Iter;

bool find(Iter begin, Iter endd, int target){
    while(begin!=endd){
        if(*begin == target) return true;
        ++begin;
    }
    return false;

}

int main(int argc, char const *argv[])
{

    vector<int> vec{1,2,3,4,5};
    cout<<find(vec.begin(),vec.end(),10)<<endl;

    return 0;
}
