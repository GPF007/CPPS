
#include "ast.h"
#include "mempool.h"

#define BUF 10
//各种mempool定义
Alloc<IntExpr> intPool(BUF);
Alloc<BinExpr> binPool(BUF);
Alloc<ParenExpr> parenPool(BUF);



//用来new的静态方法哦

IntExpr* IntExpr:: New(int val){
    return intPool.newElement(val);
}
ParenExpr* ParenExpr::New(Expr* e){
    return parenPool.newElement(e);
}
BinExpr* BinExpr::New(Expr* l ,Expr *r, TOKEN o){
    return binPool.newElement(l,r,o);
}




string Expr::to_string(){
    return string("Expr");
}

string IntExpr::to_string(){
    string res("int(");
    return res + std::to_string(val_)+ ")";
}

string BinExpr::to_string(){
    string res("bin(");
    string ls = left_->to_string();
    string rs = right_->to_string();
    string ops;
    switch (op_)
    {
    case TOKEN::PLUS: ops = "+"; break;
    case TOKEN::MINUS: ops = "-"; break;
    case TOKEN::TIMES: ops = "*"; break;
    case TOKEN::DIVIDE: ops = "/"; break;
    default:
        break;
    }
    return res + ls + ops + rs + ")";
}

string ParenExpr::to_string(){
    string res("Parent(");
    return res + expr_->to_string() + ")";
}


