#include <iostream>
#include <string>
#include <vector>
using namespace std;


//how now now now brown cow cow
int main(int argc, char const *argv[])
{
    string s;
    string res = "no such word";
    string pre;
    int count=0,tmp=1,idx=0,ans=0;

    vector<string> vec{"how","now","now","now","brown","cow","cow"};

    for(decltype(vec.size()) i = 0;i<vec.size()-1;++i){
        if(vec[i] == vec[i+1]){
            idx = i;
            ++tmp;
            ans = ans>tmp?ans:tmp;
        }else
            tmp = 1;
        count = tmp>count?tmp:count;
        ans = tmp>count?idx:ans;
    }

    
    //count = tmp>count?tmp:count;

    cout<<vec[ans]<<endl;
    cout<<count<<endl;

    return 0;
}
