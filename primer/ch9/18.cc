#include <iostream>
#include <deque>
using namespace std;

int main(int argc, char const *argv[])
{
    string s;
    deque<string> dq;
    while(cin>>s){
        dq.push_back(s);
    }

    cout<<"the elements in deque:"<<endl;

    for(auto &item:dq){
        cout<<item<<endl;
    }
    
    return 0;
}
