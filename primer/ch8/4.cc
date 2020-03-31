#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

/*一次读入文件的一个单词*/


using namespace std;

int main(int argc, char const *argv[])
{
    /* code */
    if(argc<2){
        cerr<<"arguments must be file name"<<endl;;
        exit(EXIT_FAILURE);
    }

    ifstream input(argv[1]);
    if(input){
        vector<string> vec;
        string s;
        while(input>>s)
            vec.push_back(s);

        cout<<"show words"<<endl;
        for(auto &v:vec)
            cout<<v<<endl;

    }else
        cerr<<"couldn't open:"+string(argv[1])<<endl;


    return 0;
}
