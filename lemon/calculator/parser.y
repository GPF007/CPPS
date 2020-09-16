
%include{

#include "parser.h"
#include "util.h"



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
    /*code segment*/
}