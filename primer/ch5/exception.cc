#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;


int main(int argc, char const *argv[])
{
    int a,b;
    while(cin>>a>>b){
        try{
            if(a!=b)
                throw runtime_error("a and b must be equal");
        }catch(runtime_error err){
            cout<<err.what()
                <<"\nTry Again? Enter y or n"<<endl;
            char c;
            cin>>c;
            if(!cin || c=='n')
                break;
        }
    }
    return 0;
}

