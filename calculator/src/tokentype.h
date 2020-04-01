#include <unordered_map>

enum TOKEN{
    LPAREN,
    RPAREN,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    EQUAL,

    INTEGER,
    ID,


    UNRECOG,
    eof,
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


