/*从标准输入一次读入一行*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    string line, word;
    while(getline(cin, line)){
        if(line.size() <= 80)
            cout<<line <<endl;
    }

    
    return 0;
}
