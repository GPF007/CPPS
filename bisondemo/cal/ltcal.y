/* reverse polish notation calculator */

%{
/*一些函数声明*/
#include <stdio.h>
#include <math.h>
#include <ctype.h>
int yylex (void);
void yyerror (char const *);
%}

%define api.value.type {int}
%token NUM
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
| exp '\n' { printf ("%d\n", $1); }
| error '\n' { printf("error syntax!\n");}

;
exp:
NUM
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
{ if ($3)
    $$ = $1 / $3;
    else
        {
            $$ = 1;
            fprintf(stderr, "%d.%d-%d.%d: division by zero",
            @3.first_line, @3.first_column,
            @3.last_line, @3.last_column);
        }
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
int c;
/* Skip white space. */
while ( (c = getchar()) ==' ' || c == '\t')
    ++yylloc.last_column;

yylloc.first_line = yylloc.last_line;
yylloc.first_column = yylloc.last_column;


/* Process numbers. */
if (isdigit (c))
{
    yylval = c -'0';
    ++yylloc.last_column;
    while(isdigit(c = getchar()))
    {
        ++yylloc.last_column;
        yylval = yylval*10 + c-'0';
    }
    ungetc(c, stdin);
    return NUM;
}
/* Return end-of-input. */
else if (c == EOF)
return 0;
/* Return a single char. */
else if(c=='\n'){
    ++yylloc.last_line;
    yylloc.last_column = 0;
}else
    ++yylloc.last_column;
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
    yylloc.first_line = yylloc.last_line = 1;
    yylloc.first_column = yylloc.last_column = 1;
    return yyparse ();
}