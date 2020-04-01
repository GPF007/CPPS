#include "token.h"
#include <sstream>

using namespace std;

string Token::to_string(){
    ostringstream ret;
    ret<<"filename: "<<fname_;
    ret<<" line:"<<line_;
    ret<<" column:"<<column_;
    ret<<" count:"<<count_;
    ret<<" tag:"<<tag_;
    ret<<" val: "<<value_;

    return ret.str();
}