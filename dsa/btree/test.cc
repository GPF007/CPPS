#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



int main(int argc, char const *argv[])
{
    /* code */
    vector<int> v{11,13,14,15};
    v.insert(v.begin()+1,12);
    v.insert(v.begin()+5,16);
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    //cout<<*it<<endl;
    return 0;
}
