#include <string>
#include "tokentype.h"

using std::string;

enum TOKEN;


class Token{

public:

    Token() = default;
    Token(string fname, int line, int column, int count, TOKEN tag, string value):
        fname_(fname),line_(line),column_(column), count_(count), tag_(tag), value_(value){}


    bool is_eof() { return tag_ == TOKEN::eof;}
    bool is_unknown() {return tag_ == TOKEN::UNRECOG;}

    //debug functions
    string to_string();


    

private:
    //location
    string fname_;
    int line_;
    int column_;
    //文件中第n个token
    int count_; 

    TOKEN tag_; //token的类型
    string value_; //token的字面值
   

};

