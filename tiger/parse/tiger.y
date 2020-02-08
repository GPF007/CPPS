%{
#include <stdio.h>
#include "util.h"
#include "errormsg.h"

int yylex(void); /* function prototype */

void yyerror(char *s)
{

 EM_error(EM_tokPos, "%s", s);
}
%}

%debug

%union {
	int pos;
	int ival;
	string sval;
	}
  /*终结符用 %token 开始用 %start*/
%token <sval> ID STRING
%token <ival> INT
 
%token 
  COMMA COLON SEMICOLON LPAREN RPAREN LBRACK RBRACK 
  LBRACE RBRACE DOT 
  PLUS MINUS TIMES DIVIDE EQ NEQ LT LE GT GE
  AND OR ASSIGN
  ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END OF 
  BREAK NIL
  FUNCTION VAR TYPE 

%nonassoc LOW
%nonassoc THEN DO TYPE FUNCTION ID 
%nonassoc ASSIGN LBRACK ELSE OF COMMA
%left OR
%left AND
%nonassoc EQ NEQ LE LT GT GE
%left PLUS MINUS
%left TIMES DIVIDE
%left UMINUS
  

%start program

%%

/* This is a skeleton grammar file, meant to illustrate what kind of
 * declarations are necessary above the %% mark.  Students are expected
 *  to replace the two dummy productions below with an actual grammar. 
 */

program:	optexp {printf("start symbol!\n");}
;

optexp:     exp
      |     
      ;
exp:        lvalue
        |   nonvalue
        |   NIL
        |   LPAREN optexpseq RPAREN
        |   INT
        |   MINUS exp 
        |   STRING 
        |   call 
        |   biops
        |   record_creat
        |   id LBRACK exp RBRACK OF exp 
        |   lvalue ASSIGN exp 
        |   LET decs IN optexpseq END 
        |   BREAK
        ;


optexpseq:  expseq 
        |
               
         ;
expseq:     exp SEMICOLON expseq
        |   exp 
        ;

call:   ID LPAREN optargs RPAREN ;

optargs:  args
        |    
        ;
;
args:       exp COMMA args
        |   exp
        ;

biops:      exp PLUS   exp
        |   exp MINUS  exp 
        |   exp TIMES  exp 
        |   exp DIVIDE exp
        |   exp EQ     exp 
        |   exp LT     exp
        |   exp LE     exp
        |   exp GE     exp
        |   exp GT     exp
        |   exp NEQ    exp
        |   exp AND    exp
        |   exp OR     exp
        ;

record_creat:     LBRACE optassig RBRACE ;
optassig:        assig 
        |
        ;
assig:            ID EQ exp COMMA assig
          |       ID EQ exp 
          ;
nonvalue:       IF exp THEN exp ELSE exp 
        |       IF exp THEN exp 
        |       WHILE exp DO exp
        |       FOR ID ASSIGN exp TO exp DO exp
        ;

decs:       dec decs 
        |   
;
dec:        tydec
        |   vardec
        |   fundec
;
tydec:      TYPE id EQ ty ;
          

ty:         id  
        |   LBRACE tyfields RBRACE
        |   ARRAY OF id
        ;

tyfields:   ID COLON id COMMA tyfields
        |   ID COLON id
        |
        ;

vardec:     VAR ID ASSIGN exp 
        |   VAR ID COLON id ASSIGN exp
        ;

fundec:     FUNCTION  ID  LPAREN tyfields RPAREN EQ exp 
        |   FUNCTION  ID  LPAREN tyfields RPAREN COLON id EQ exp
        ;

lvalue:     id %prec LOW
        |   lvalue  DOT ID 
        |   lvalue  LBRACK exp RBRACK
        |   id LBRACK exp RBRACK 
        ;

id:    ID ;

%%