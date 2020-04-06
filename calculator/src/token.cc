#include "token.h"
#include <sstream>
#include "mempool.h"


Alloc<Token> tokenPool(10);


using namespace std;


Token* Token::New(const string *fname, int line, int column, int count, TOKEN tag, const string* value)
{
    Token* ret = tokenPool.newElement(fname,line,column,count,tag,value);
    return ret;
}

string Token::to_string(){
    ostringstream ret;
    ret<<"filename: "<<*fname_;
    ret<<" line:"<<line_;
    ret<<" column:"<<column_;
    ret<<" count:"<<count_;
    ret<<" tag:"<<tag_;
    ret<<" val: "<<*value_;

    return ret.str();
}