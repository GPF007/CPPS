#include "parse.h"
#include <iostream>
#include <unordered_map>

using std::cout;
using std::endl;



void Parser::show(){
    //for(auto &tok:token_list)
      //  cout<<tok->to_string()<<endl;
    int i = 1;
    for(auto e:expList){
        cout<<"Expr: "<<i++<<endl;
        cout<<e->to_string()<<endl;
    }
}


Expr* Parser::parse(){

    while(!peek()->is_eof()){
        expList.push_back(parse_additive());
        tryy(TOKEN::SEMI);
    }


    return expList.front();
}

Expr* Parser::parse_additive(){
    //cout<<"parse_additive:"<<endl;

    Expr* lhs = parse_multive();
    auto cur = next();
    while(cur->get_tag()==TOKEN::PLUS || cur->get_tag() == TOKEN::MINUS){
        Expr* rhs = parse_multive();
        //lhs = new  BinExpr(lhs,rhs,cur->get_tag());
        lhs = BinExpr::New(lhs,rhs,cur->get_tag());
        cur = next();
    }

    put_back();
    return lhs;

}

Expr* Parser::parse_multive(){
    //cout<<"parse_multive:"<<endl;
    Expr* lhs = parse_primary();
    auto cur = next();
   // cout<<"cur token in multive: "<<*peek()->get_val()<<endl;
    while(cur->get_tag()==TOKEN::TIMES || cur->get_tag() == TOKEN::DIVIDE){
        Expr* rhs = parse_primary();
        //lhs = new BinExpr(lhs,rhs, cur->get_tag());
        lhs = BinExpr::New(lhs,rhs,cur->get_tag());
        cur = next();
    }
    put_back();
    return lhs;
}

Expr* Parser::parse_primary(){
    //cout<<"parse_primary:"<<endl;
    auto cur = next();
    if(cur->get_tag()==TOKEN::INTEGER){
        put_back();
        return parse_int();
    }else if(cur->get_tag() == TOKEN::LPAREN){
        Expr* lhs = parse_additive();
        //expect(TOKEN::RPAREN);
        //next();
        tryy(TOKEN::RPAREN);
        lhs = ParenExpr::New(lhs);
        return lhs;
    }
    return 0;
}


Expr* Parser::parse_int(){
    //cout<<"parse_int:"<<endl;
    auto cur = next();
    //cout<<"integer val: "<<*cur->get_val()<<endl;

    //Expr *ret = new IntExpr(std::stoi(*cur->get_val()));
    Expr *ret = IntExpr::New(std::stoi(*cur->get_val()));
    return ret;
}

