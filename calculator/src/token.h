#pragma once

#include <string>
#include <vector>
#include "tokentype.h"

#include <iostream>

using std::string;

// enum TOKEN;



class Token{

public:

    Token() = default;
    Token(const string *fname, int line, int column, int count, TOKEN tag, const string* value):
        fname_(fname),line_(line),column_(column), count_(count), tag_(tag), value_(value){}
    
    static Token* New(const string *fname, int line, int column, int count, TOKEN tag, const string* value);


    bool is_eof() { return tag_ == TOKEN::eof;}
    bool is_unknown() {return tag_ == TOKEN::UNRECOG;}
    TOKEN get_tag() { return tag_; }
    const string* get_val() {return value_;}

    //debug functions
    string to_string();    

private:
    //location
    const string *fname_;
    int line_;
    int column_;
    //文件中第n个token
    int count_; 

    TOKEN tag_; //token的类型
    const string *value_; //token的字面值
};


class TokenList{


public:
    TokenList() = default;

    void show(){
        for(auto &tok:token_list){
            std::cout<<tok->to_string()<<std::endl;
        }
    }
    
    void add(Token* t) {token_list.push_back(t);}

    Token*& next(){return (token_list)[idx++];}
    Token*& peek(){return (token_list)[idx];}
    void put_back() {--idx;}
    void expect();


private:
    std::vector<Token*> token_list;
    size_t idx=0;
};


