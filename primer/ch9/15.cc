#include <iostream>
#include <vector>
#include <list>

using namespace std;

bool isEqualVector(vector<int>& v1, vector<int>& v2){
    return v1 == v2;
}

bool isEqual(vector<int>& v1, list<int> &l){
    return vector<int>(l.begin(),l.end()) == v1;
}

int main(int argc, char const *argv[])
{
    vector<int> vec1{1,2,3};
    vector<int> vec2{1,2,3};
    cout<<isEqualVector(vec1,vec2)<<endl;
    return 0;
}

