#include "scanner.h"
#include "sym.h"
#include <cctype>
#include <iostream>
#include <unordered_map>


using std::endl;
using std::cout;

extern Sym sym;

std::unordered_map<TOKEN,std::string> tagliteral{
    {TOKEN::PLUS,"+"},
    {TOKEN::MINUS,"-"},
    {TOKEN::TIMES,"*"},
    {TOKEN::DIVIDE,"/"},
    {TOKEN::LPAREN,"("},
    {TOKEN::RPAREN,")"},
    {TOKEN::IF,"if"},
    {TOKEN::RETURN,"return"},
    {TOKEN::SEMI,";"},
};

std::unordered_map<std::string,TOKEN> keywords{
    {"if",TOKEN::IF},
    {"return",  TOKEN::RETURN}
};


/*
std::unordered_map<char,std::string> table{
    {'+',"+"},
    {'-',"-"},
    {'*',"*"},
    {'/',"/"},
    {'(',"("},
    {')',")"},
};
*/







void Scanner::skipWhite(){
    int cur = next();
    while( cur == ' '||cur=='\t' || cur =='\r' || cur =='\n'){
        cur = next();
    }
    put_back(cur);
}

Scanner::Scanner(std::string *fname){
    fname_ = fname;
    in_.open(fname_->c_str());
    if(!in_.good()){
        cout<<"open file faied"<<endl;
        exit(EXIT_FAILURE);
    }
}



Token* Scanner::make_token(TOKEN tag, const string *val){
    //return token_pool.newElement(fname_, line_, column_, count_++, tag, val);
    //return new Token(fname_, line_, column_, count_++, tag, val);
    return Token::New(fname_, line_, column_, count_++, tag, val);
}

Token* Scanner::make_integer(int cur){
    tmp_.clear();
    //int cur = next();
    while(isdigit(cur)){
        tmp_.append(1,char(cur));
        cur = next();
    }
    //读取完数字之后退回到流中
    put_back(cur);

    return make_token(TOKEN::INTEGER,sym.get_sym_full(tmp_));
}

Token* Scanner::make_identifier(int cur){
    tmp_.clear();
    while(isalnum(cur)){
        tmp_.append(1,char(cur));
        cur = next();
    }
    //读取完标识符之后退回到流中
    put_back(cur);

    auto it = keywords.find(tmp_);
    if(it == keywords.end())//说明不是关键字返回一个identifier
        return make_token(TOKEN::ID,sym.get_sym_full(tmp_));
    return make_token(it->second, sym.get_sym_full(tmp_));

}




Token* Scanner::Scan(){
    skipWhite();
    auto cur = next();
    //cout<<cur<<" ";
    if(cur == EOF)
        return make_token(TOKEN::eof, sym.get_sym_full("EOF"));

    switch (cur)
    {
    case '+': return make_token(TOKEN::PLUS, sym.get_sym_full(tagliteral[TOKEN::PLUS]));
    case '-': return make_token(TOKEN::MINUS, sym.get_sym_full(tagliteral[TOKEN::MINUS]));
    case '*': return make_token(TOKEN::TIMES, sym.get_sym_full(tagliteral[TOKEN::TIMES]));
    case '/': return make_token(TOKEN::DIVIDE, sym.get_sym_full(tagliteral[TOKEN::DIVIDE]));
    case '(': return make_token(TOKEN::LPAREN, sym.get_sym_full(tagliteral[TOKEN::LPAREN]));
    case ')': return make_token(TOKEN::RPAREN, sym.get_sym_full(tagliteral[TOKEN::RPAREN]));
    case ';': return make_token(TOKEN::SEMI, sym.get_sym_full(tagliteral[TOKEN::SEMI]));
    case '0' ... '9':  return make_integer(cur);
    case 'a' ... 'z':  return make_identifier(cur);
    case EOF: return make_token(TOKEN::eof, sym.get_sym_full("EOF"));
    default:
        return make_token(TOKEN::UNRECOG, sym.get_sym_full("UNRECOGNIZE"));
    }


    return make_token(TOKEN::UNRECOG, sym.get_sym_full("UNRECOGNIZE"));
}


int Scanner::next(){
    int cur = in_.get();
    if(cur == '\n'){
        pre_column = column_;
        column_=1;
        ++line_;
    }else
        ++column_;

    return cur;
}
    
int Scanner::peek(){
    int pek= in_.get();
    in_.unget();
    return pek;
}

void Scanner::put_back(int c){

    if(c == '\n'){
        --line_;
        column_ = pre_column;
    }else
        --column_;
    //退回到流中一个值
    in_.unget();

}
void Scanner::expect(int expected){
    int pek = peek();
    if(expected != peek()){
        fprintf(stderr,"expected %c but got %c",expected,pek);
        exit(EXIT_FAILURE);
    }
}
int tr();




