#include "scanner.h"
#include "sym.h"
#include <cctype>
#include <iostream>
#include <unordered_map>


using std::endl;
using std::cout;


extern Sym sym;


std::unordered_map<char,std::string> table{
    {'+',"+"},
    {'-',"-"},
    {'*',"*"},
    {'/',"/"},
    {'(',"("},
    {')',")"},
};





void Scanner::skipWhite(){

    while( ch_ == ' '||ch_=='\t' || ch_ =='\r' || ch_ =='\n'){
        readChar();
    }
}

Scanner::Scanner(std::string fname){
    fname_ = fname;
    in_.open(fname_.c_str());
    if(!in_.good()){
        cout<<"open file faied"<<endl;
        exit(EXIT_FAILURE);
    }
}

void Scanner::readChar(){
    ch_ = in_.get();
    //cout<<"ch_"<<endl;
    
    if(ch_ == '\n'){
        pre_column = column_;
        column_=1;
        ++line_;
    }else
        ++column_;

}

void Scanner::put_back(){
    if(ch_ == '\n'){
        --line_;
        column_ = pre_column;
    }else
        --column_;
    //退回到流中一个值
    in_.unget();
}

Token Scanner::make_token(TOKEN tag, const string *val){
    return Token(&fname_, line_, column_, count_++, tag, val);
}

Token Scanner::make_integer(){
    string tmp;
    while(isdigit(ch_)){
        tmp.append(1,char(ch_));
        readChar();
    }
    //读取完数字之后退回到流中
    put_back();

    return make_token(TOKEN::INTEGER,sym.get_sym_full(tmp));
}

Token Scanner::make_identifier(){
    string tmp;
    while(isalnum(ch_)){
        tmp.append(1,char(ch_));
        readChar();
    }
    //读取完标识符之后退回到流中
    put_back();

    return make_token(TOKEN::INTEGER,sym.get_sym_full(tmp));

}




Token Scanner::Scan(){
    readChar();

    skipWhite();
    switch (ch_)
    {
    case '+': return make_token(TOKEN::PLUS, sym.get_sym_full(table['+']));
    case '-': return make_token(TOKEN::MINUS, sym.get_sym_full(table['-']));
    case '*': return make_token(TOKEN::TIMES, sym.get_sym_full(table['*']));
    case '/': return make_token(TOKEN::DIVIDE, sym.get_sym_full(table['/']));
    case '(': return make_token(TOKEN::LPAREN, sym.get_sym_full(table['(']));
    case ')': return make_token(TOKEN::RPAREN, sym.get_sym_full(table[')']));
    case '0' ... '9': return make_integer();
    case 'a' ... 'z': return make_identifier();
    case EOF: return make_token(TOKEN::eof, sym.get_sym_full("EOF"));
    default:
        return make_token(TOKEN::UNRECOG, sym.get_sym_full("UNRECOGNIZE"));
    }


    return make_token(TOKEN::UNRECOG, sym.get_sym_full("UNRECOGNIZE"));
}




