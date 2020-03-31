#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>

/*一次读入文件的一行*/


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
        while(getline(input,s,'\n'))
            vec.push_back(s);
        

        cout<<"show lines with istringstream"<<endl;
        int i=0;
        for(auto &v:vec){
            i+=1;
            istringstream is(v);
            string ans;
            cout<<"line:"<<i<<" ";
            while(is >> ans)
                cout<<ans<<" ";
            cout<<endl;
            
        }

    }else
        cerr<<"couldn't open:"+string(argv[1])<<endl;


    return 0;
}
