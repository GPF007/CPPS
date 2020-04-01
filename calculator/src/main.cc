#include <iostream>
#include <cstdlib>
#include "scanner.h"

using namespace std;

int main(int argc, char const *argv[])
{
    cout<<"hello world!"<<endl;
    string fname = string("test.cc");
    string value = string("123");
    Token t1(fname, 0, 1, 0, TOKEN::EQUAL,value);
    cout<<t1.to_string()<<endl;
    if(argc<2){
        cerr<<"usage: ./main <filename>"<<endl;
        exit(EXIT_FAILURE);
    }
    Scanner scanner(argv[1]);

    Token tok;
    int i =0;
    for(;;){
        tok = scanner.Scan();
        if(tok.is_eof()) break;
        cout<<tok.to_string()<<endl;
        ++i;
          //if(i==14) break;
    }




    return 0;
}
