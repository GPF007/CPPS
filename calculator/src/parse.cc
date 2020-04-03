#include "parse.h"
#include <iostream>

using std::cout;
using std::endl;

void Parser::show(){
    for(auto &tok:token_list)
        cout<<tok.to_string()<<endl;
}


Expr* Parser::parse(){

    //cout<<"parse_additive:"<<endl;

    return parse_additive();
}

Expr* Parser::parse_additive(){

    Expr* lhs = parse_multive();
    auto cur = next();
    while(cur.get_tag()==TOKEN::PLUS || cur.get_tag() == TOKEN::MINUS){
        Expr* rhs = parse_multive();
        lhs = new BinExpr(lhs,rhs,cur.get_tag());
        cur = next();
    }

    put_back();
    return lhs;

}

Expr* Parser::parse_multive(){
    Expr* lhs = parse_primary();
    auto cur = next();
    //cout<<"cur token in multive: "<<*peek().get_val()<<endl;
    while(cur.get_tag()==TOKEN::TIMES || cur.get_tag() == TOKEN::DIVIDE){
        Expr* rhs = parse_primary();
        lhs = new BinExpr(lhs,rhs, cur.get_tag());
        cur = next();
    }
    put_back();
    return lhs;
}

Expr* Parser::parse_primary(){
    auto cur = next();
    if(cur.get_tag()==TOKEN::INTEGER){
        put_back();
        return parse_int();
    }else if(cur.get_tag() == TOKEN::LPAREN){
        Expr* lhs = parse_additive();
        expect(TOKEN::RPAREN);
        next();
        lhs = new ParenExpr(lhs);
        return lhs;
    }
    return 0;
}


Expr* Parser::parse_int(){
    Token &tok = next();
    cout<<"integer val: "<<*tok.get_val()<<endl;

    Expr *ret = new IntExpr(std::stoi(*tok.get_val()));
    return ret;
}

