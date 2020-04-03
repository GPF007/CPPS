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
    Scanner scanner(argv[1]);

    Token tok;
    int i =0;

    vector<Token> token_list;
    
    
    for(;;){
        tok = scanner.Scan();
        token_list.push_back(tok);
        if(tok.is_eof()) break;
        //cout<<tok.to_string()<<endl;
        ++i;
          //if(i==14) break;       
    }

    Parser parser(token_list);
    parser.show();

    //int res = parser.parse();
    Expr* expr = parser.parse();
    cout<<expr->to_string()<<endl;


   //Sym::put_sym(20);


    
   




    return 0;
}
