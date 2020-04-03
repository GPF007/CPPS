
#include "ast.h"

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

