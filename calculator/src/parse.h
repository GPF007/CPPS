#include <vector>
#include <cstdlib>
#include <cstdio>
#include "ast.h"
#include "token.h"


class Parser{

public:
    Parser(std::vector<Token> &tl): token_list(tl) { cur = 0; pek = 1; sz = tl.size(); }


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
    std::vector<Token> &token_list;

    Token *cur_tok;

    size_t cur, pek, sz;
    //help functions
    Token& peek() {return token_list[cur];}
    Token& next() {return token_list[cur++];}
    void expect(TOKEN tag) { 
        if(peek().get_tag()!=tag)
        {   fprintf(stderr,"expected (!"); 
            exit(EXIT_FAILURE);
        } 
     }
    void tr(Token expected_tok) {if(peek().get_tag()==expected_tok.get_tag()) next();}
    void put_back() {--cur;}
    




};
