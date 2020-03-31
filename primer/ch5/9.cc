#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    string s;
    while(cin>>s){
        int a,e,i,o,u = 0;
        int total=0;

        for(auto &ch:s){
            switch(ch)
            {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                total++;
                break;
            default:
                break;

            }
        }

        cout<<"The total vowel counts is "<<total<<endl;

    }
    return 0;
}
