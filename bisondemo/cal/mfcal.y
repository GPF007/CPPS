/* reverse polish notation calculator */

%{
/*一些函数声明*/
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "cal.h" /* for symrec*/
int yylex (void);
void yyerror (char const *);
%}

%define api.value.type union
%token <double> NUM
%token <symrec*> VAR FUN
%nterm <double> exp /*%nterm 用来定义非终结符*/

%precedence '='
%left '-' '+'
%left '*' '/'
%precedence NEG
%right '^'


%% /*下面是语法规则*/
input:
%empty
| input line
;
line:
'\n'
| exp '\n' { printf ("%.10g\n", $1); }
| error '\n' { printf("error syntax!\n");}

;
exp: NUM
| VAR {$$ = $1->value.var;}
| VAR '=' exp {$$ = $3; $1->value.var = $3}
| FUN '(' exp ')' { $$ = $1->value.fun($3);}
| exp '+' exp
{ $$ = $1 + $3;
}
| exp '-' exp
{ $$ = $1 - $3;
}
| exp '*' exp
{ $$ = $1 * $3;
}
| exp '/' exp
{ $$ = $1 / $3;
}
| exp '^' exp
{ $$ = pow($1, $3); } /* Exponentiation */
| '-' exp %prec NEG
{ $$ = -$2;} /* Unary minus*/
| '(' exp ')' { $$ = $2;}
;
%%


int
yylex (void)
{
int c = getchar ();
/* Skip white space. */
while (c ==  ' ' || c == '\t')
c = getchar ();
/* Process numbers. */
if (c == '.' || isdigit (c))
{
ungetc (c, stdin);
scanf ("%lf", &yylval);
return NUM;
}
/* Return end-of-input. */
else if (c == EOF)
return 0;
/* Return a single char. */
else
return c;
}

void
yyerror (char const *s)
{
fprintf (stderr, "%s\n", s);
}

int
main (void)
{
return yyparse ();
}