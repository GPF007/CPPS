#include <iostream>
#include <cstdlib>
#include <vector>
#include "scanner.h"
#include "sym.h"
#include "parse.h"




using namespace std;
Sym sym;

int main(int argc, char const *argv[])
{
    cout<<"hello world!"<<endl;
    if(argc<2){
        cerr<<"usage: ./main <filename>"<<endl;
        exit(EXIT_FAILURE);
    }
    string fname = string(argv[1]);
    Scanner scanner(&fname);
    TokenList token_list;

    Token *tok;
    int i =0;

    
    for(;;){
        tok = scanner.Scan();
        //cout<<"make token done!"<<endl;
        token_list.add(tok);
        if(tok->is_eof()) break;
       // cout<<tok->to_string()<<endl;
        ++i;
          //if(i==14) break;       
    }
    token_list.show();

    
    Parser parser(&token_list);
    //parser.show();

    //int res = parser.parse();
    Expr* expr = parser.parse();
    parser.show();
    //cout<<expr->to_string()<<endl;
    

   //Sym::put_sym(20);


    
   




    return 0;
}
