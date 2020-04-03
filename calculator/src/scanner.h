
#include <fstream>
#include "token.h"



using std::string;



class Scanner{

public:
    Scanner() = default;
    Scanner(std::string fname);


    Token Scan(); 


    void skipWhite();
    void readChar();
    void put_back();

    Token make_token(TOKEN tag, const string *val);
    Token make_integer();
    Token make_identifier();

private:
    string fname_;
    std::ifstream in_;

    int line_=1;
    int column_=1;
    int pre_column = 0;
    int count_=0;
    int ch_ = 0;


    //当前的string literal
    string cur;
    

};