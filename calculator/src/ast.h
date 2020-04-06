#include <string>

#include "tokentype.h"

using std::string;

class Node{
public:
    virtual std::string to_string() = 0;

    virtual ~Node() {}
  
};

class Expr : public Node{
public:
    string to_string() override;
};

class BinExpr : public Expr{
public:
    BinExpr(Expr* l ,Expr *r, TOKEN o): left_(l),right_(r), op_(o){}
    static BinExpr* New(Expr* l ,Expr *r, TOKEN o);


    string to_string() override;
protected:
    Expr *left_;
    Expr *right_;
    TOKEN op_;
    
};

class IntExpr: public Expr{
public:

    IntExpr(int val):val_(val){}
    static IntExpr* New(int val);
    string to_string() override;

protected:
    int val_;
    

};

class ParenExpr: public Expr{
public:

    ParenExpr(Expr* e):expr_(e) {}
    static ParenExpr* New(Expr* e);
    string to_string() override;

protected:
    Expr* expr_;
};


