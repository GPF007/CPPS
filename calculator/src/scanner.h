
#include <fstream>
#include "token.h"
#include "mempool.h"


using std::string;



class Scanner{

public:
    Scanner() = default;
    Scanner(std::string *fname);


    Token* Scan(); 


    void skipWhite();
    void readChar();
    void put_back(int c);

    Token* make_token(TOKEN tag, const string *val);
    Token* make_integer(int);
    Token* make_identifier(int);
    Token* make_keyword();

    int next();
    int peek();
    void expect(int);
    int tr();


private:
    string *fname_;
    std::ifstream in_;

    int line_=1;
    int column_=1;
    int pre_column = 0;
    int count_=0;


    string tmp_;

    

};