#include "scanner.h"
#include <cctype>
#include <iostream>

using std::endl;
using std::cout;

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

Token Scanner::make_token(TOKEN tag, string val){
    return Token(fname_, line_, column_, count_++, tag, val);
}

Token Scanner::make_integer(){
    string tmp;
    while(isdigit(ch_)){
        tmp.append(1,char(ch_));
        readChar();
    }
    //读取完数字之后退回到流中
    put_back();

    return make_token(TOKEN::ID, tmp);
}

Token Scanner::make_identifier(){
    string tmp;
    while(isalnum(ch_)){
        tmp.append(1,char(ch_));
        readChar();
    }
    //读取完标识符之后退回到流中
    put_back();
    return make_token(TOKEN::INTEGER, tmp);

}



Token Scanner::Scan(){
    readChar();

    skipWhite();
    switch (ch_)
    {
    case '+': return make_token(TOKEN::PLUS, "+");
    case '-': return make_token(TOKEN::MINUS, "-");
    case '*': return make_token(TOKEN::TIMES, "*");
    case '/': return make_token(TOKEN::DIVIDE, "/");
    case '(': return make_token(TOKEN::LPAREN, "(");
    case ')': return make_token(TOKEN::RPAREN, ")");
    case '0' ... '9': return make_integer();
    case 'a' ... 'z': return make_identifier();
    case EOF: return make_token(TOKEN::eof, "EOF");;
    default:
        return make_token(TOKEN::UNRECOG, "UNRECOGNIZE");
    }

    return make_token(TOKEN::UNRECOG, "UNRECOGNIZE");
}


