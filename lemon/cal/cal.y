
%include{

#include "cal.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define NUMBER 20

typedef struct {
    char* name;
    double value;
    double (*funcptr)(double);
    double (*funcptr2)(double, double);
}Symbol;

typedef union
{
    Symbol* symt;
    double value;
}Token;

void token_destructor(Token t){
;
}
}


%token_type {Token}
%default_type {Token}
%token_destructor{token_destructor($$);}

%left PLUS MINUS .
%left DIVIDE TIMES .
%right POW NOT .

%parse_accept{
    printf("parsing complete!\n");
}

%syntax_error {
    printf("Syntax error!\n");
    exit(1);
}



/* start of rules*/
main ::= in.
in ::= in NEWLINE.
in ::= .
in ::= in program NEWLINE.

program ::= NAME(A) EQ expr(B).
    {
        if(A.symt->funcptr || A.symt->funcptr2){
            printf("%s is a function! Must type in rightside!\n", A.symt->name);
            A.symt->value = 0.0;
        }else{
            A.symt->value = B.value;
        }
    }

program ::= expr(A) . {printf("= %lf\n",A.value);}

expr(A) ::= expr(B) MINUS expr(C). {A.value = B.value - C.value;}

expr(A) ::= expr(B) PLUS expr(C). {A.value = B.value + C.value;}

expr(A) ::= expr(B) TIMES expr(C). {A.value = B.value * C.value;}

expr(A) ::= expr(B) DIVIDE expr(C). {A.value = B.value / C.value;}

expr(A) ::= expr(B) POW expr(C). {A.value = pow(B.value, C.value);}

expr(A) ::= LP expr(B) RP . {A.value = B.value;}

expr(A) ::= NUM(B). {A.value = B.value;}

expr(A) ::= NAME(B). 
    {
        if(B.symt->funcptr || B.symt->funcptr2){
            printf("%s is a function! Must type in like a number!\n", B.symt->name);
            A.value = 0.0;
        }else{
            A.value = B.symt->value;
        }
    }

expr(A) ::= NAME(B) LP expr(C) RP.
    {
        printf("B.symt->name is [%s]\n",B.symt->name);
        if(B.symt->funcptr){
            A.value = (B.symt->funcptr) (C.value);
        }else{
            printf("[%s] function undifined! func1 \n",B.symt->name);
            exit(1);
        }
    }

expr(A) ::= NAME(B) LP expr(C) COMMA expr(D) RP.
    {
        if(B.symt->funcptr2){
            A.value = (B.symt->funcptr2) (C.value, D.value);
        }else{
            printf("%s function undifined! func2 \n",B.symt->name);
            exit(1);
        }
    }

%code{
static int getToken(const char* z, int *tokenType){
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

static char* getstring(char* z, int n){
    char* paz;
    paz = (char*)malloc(n+1);
    if(paz ==0){
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strncpy(paz, z, n);
    paz[n]='\n';
    return paz;
}

static Symbol* symlook(char* s, Symbol* symtab){
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

static void addfunc(char* name, double (*func)(double x), Symbol* symtab)
{
    Symbol* sp = symlook(name, symtab);
    sp->funcptr = func;
    printf("add function [%s] done!\n", name);
}

static void addfunc2(char* name, double (*func)(double x,double y), Symbol* symtab)
{
    Symbol* sp = symlook(name, symtab);
    sp->funcptr2 = func;
}

int main(){
    FILE* f;
    f = fopen("record.txt","w");
    ParseTrace(f,"");
    Token *t0;
    int n;
    char* z;
    int* tokenType;
    Symbol symtab[NUMBER];

    for(int i=0;i<NUMBER;i++){
        symtab[i].value = 0.0;
        symtab[i].name = NULL;
        symtab[i].funcptr = NULL;
        symtab[i].funcptr2 = NULL;
    }

    addfunc("exp", exp, symtab);
    addfunc("log", log, symtab);
    addfunc("sqrt", sqrt, symtab);
    addfunc2("pow",pow, symtab);

    t0 = (Token*)malloc(sizeof(Token));
    t0->value = 0.0;
    t0->symt = NULL;

    tokenType = (int*)malloc(sizeof(int));
    z = (char*)malloc(1024);
    void* pParser = ParseAlloc(malloc);

    while(1){
        gets(z);
        if(z=="") break;
        strcat(z,"\n");
        while(*z){
            n = getToken(z, tokenType);
            if(*tokenType == NUM){
                char* s = getstring(z,n);
                t0->value = atof(s);
            }else if(*tokenType == NAME){
                char* s = getstring(z,n);
                t0->symt = symlook(s, symtab);
            }

            if(*tokenType >=0){
                Parse(pParser, *tokenType, *t0);
            }
            z = z+n;
        }
    }

    Parse(pParser, 0, *t0);
    ParseFree(pParser, free);
    return 0;
}

}