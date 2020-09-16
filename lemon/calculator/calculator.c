
#include "calculator.h"
#include "parser.h"
#include "util.h"


//从字符串z中返回一个token的长度，类型存储在tokentype
int getToken(const char* z, int *tokenType){
    int i,c;
    switch (*z)
    {
    case '\n':
        /* code */
        *tokenType = NEWLINE;
        return 1;
    case '-':
        *tokenType = MINUS;
        return 1;
    case '+':
        *tokenType = PLUS;
        return 1;
    case '*':
        *tokenType = TIMES;
        return 1;
    case '/':
        *tokenType = DIVIDE;
        return 1;
    case '^':
        *tokenType = POW;
        return 1;
    case '(':
        *tokenType = LP;
        return 1;
    case ')':
        *tokenType = RP;
        return 1;
    case '=':
        *tokenType = EQ;
        return 1;
    case ',':
        *tokenType = COMMA;
        return 1;

    case 'a'...'z':
    case 'A'...'Z':
    {
        for(i=1;isalnum(z[i]) || z[i]=='_';i++) ;
        *tokenType = NAME;
        return i;
    }

    case '0'...'9':
    {
        for(i=1;isdigit(z[i]);i++) ;
        if(z[i]=='.' && isdigit(z[i+1])){
            i+=2;
            while(isdigit(z[i++])) ;
        }
        *tokenType = NUM;
        return i;
    }
    default:
        *tokenType = -1;
        return 1;
    }
}

char* getstring(char* z, int n){
    char* paz;
    paz = (char*)malloc(n+1);
    if(paz ==0){
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strncpy(paz, z, n);
    paz[n]='\0';
    return paz;
}

//在symtab中查找
Symbol* symlook(char* s, Symbol* symtab){
    Symbol* sp;
    for(sp = symtab; sp < &symtab[NUMBER];sp++){
        if(sp->name && !strcmp(sp->name, s)){
            return sp;
        }
        if(!sp->name){
            sp->name = s;
            return sp;
        }
    }
    exit(1);
    return NULL;
}

void addfunc(char* name, double (*func)(double x), Symbol* symtab)
{
    Symbol* sp = symlook(name, symtab);
    sp->funcptr = func;
    printf("add function [%s] done!\n", name);
}

void addfunc2(char* name, double (*func)(double x,double y), Symbol* symtab)
{
    Symbol* sp = symlook(name, symtab);
    sp->funcptr2 = func;
}