#include <iostream>
#include <cstddef>
#include <vector>

using namespace std;

using Iter = vector<int>::const_iterator;
/*print a vector*/

void printv(Iter first, Iter last){
    if(first!=last){
        cout<<*first<<" ";
        printv(++first,last);
    }
}


int main(int argc, char const *argv[])
{
    vector<int> vec{1,2,3,4,5};
    printv(vec.cbegin(),vec.cend());
    
    
    return 0;
}
