#include <vector>
#include <cstdlib>
#include <cstdio>
#include <unordered_map>
#include "ast.h"
#include "token.h"
#include "mempool.h"


extern std::unordered_map<TOKEN,std::string> tagliteral;

class Parser{

public:
    Parser(TokenList* tl): token_list(tl) { }


    //for debug
    void show();

    Expr* parse();
    int parse_parent();
    int parse_binop(int);
    Expr* parse_int();
    Expr* parse_additive();
    Expr* parse_multive();
    Expr* parse_primary();




private:
    TokenList *token_list;
    Token *cur_tok;

    std::vector<Expr*> expList;

    
    
    //help functions
    Token*& peek() {return token_list->peek();}
    Token*& next() {return token_list->next();}
    void expect(TOKEN tag) { 
        if(peek()->get_tag()!=tag)
        {   fprintf(stderr,"expected %s but got %s\n",tagliteral[tag].c_str(), 
            tagliteral[peek()->get_tag()].c_str()); 
            exit(EXIT_FAILURE);
        } 

    }

    void tryy(TOKEN tag){
        expect(tag);
        next();
    }

    //void tr(Token* expected_tok) {if(peek()->get_tag()==expected_tok->get_tag()) next();}
    void put_back() {token_list->put_back();}
    


};
