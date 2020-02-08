%{
#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"

int charPos=1;

int yywrap(void);


void adjust(void);

%}

/*定义状态 INITIAL是默认状态，不需要定义 哦 */
%s COMMENT
%s COMMENT2



%%

<INITIAL>"/*"   {adjust(); BEGIN COMMENT;}
<COMMENT>"*/"    {adjust(); BEGIN INITIAL;}
<COMMENT>.       {continue;}
<COMMENT>\n       {EM_newline(); continue;}
<INITIAL>"//"   {adjust(); BEGIN COMMENT2;}
<COMMENT2>\n    {adjust();EM_newline(); BEGIN INITIAL;}
<COMMENT2>.     {continue;}
    /*忽略的符号*/
<INITIAL>" "	 {adjust(); continue;}
<INITIAL>\t {adjust(); continue;}
<INITIAL>\n	 {adjust(); EM_newline(); continue;}
    /* 符号 */
<INITIAL>,	 {adjust(); return COMMA;}
<INITIAL>;  {adjust(); return SEMICOLON;}
<INITIAL>\( {adjust(); return LPAREN;}
<INITIAL>\) {adjust(); return RPAREN;}
<INITIAL>\[ {adjust(); return LBRACK;}
<INITIAL>\] {adjust(); return RBRACK;}
<INITIAL>\{ {adjust(); return LBRACE;}
<INITIAL>\} {adjust(); return RBRACE;}
<INITIAL>\. {adjust(); return DOT;}
<INITIAL>\+ {adjust(); return PLUS;}
<INITIAL>-  {adjust(); return MINUS;}
<INITIAL>\* {adjust(); return TIMES;}
<INITIAL>\/ {adjust(); return DIVIDE;}
<INITIAL>=  {adjust(); return EQ;}
<INITIAL>"<>" {adjust(); return NEQ;}
<INITIAL>"<"  {adjust(); return LT;}
<INITIAL>"<=" {adjust(); return LE;}
<INITIAL>">"  {adjust(); return GT;}
<INITIAL>">=" {adjust(); return GE;}
<INITIAL>"&"  {adjust(); return AND;}
<INITIAL>"|"  {adjust(); return OR;}
<INITIAL>":=" {adjust(); return ASSIGN;} 
<INITIAL>":"  {adjust(); return COLON;}
    /*所有的关键字
    */
<INITIAL>for  	 {adjust(); return FOR;}
<INITIAL>while   {adjust(); return WHILE;}
<INITIAL>array   {adjust(); return ARRAY;}
<INITIAL>if      {adjust(); return IF;}
<INITIAL>then    {adjust(); return THEN;}
<INITIAL>else    {adjust(); return ELSE;}
<INITIAL>to      {adjust(); return TO;}
<INITIAL>do      {adjust(); return DO;}
<INITIAL>let     {adjust(); return LET;}
<INITIAL>in      {adjust(); return IN;}
<INITIAL>end     {adjust(); return END;}
<INITIAL>of      {adjust(); return OF;}
<INITIAL>break   {adjust(); return BREAK;}
<INITIAL>nil     {adjust(); return NIL;}
<INITIAL>function {adjust(); return FUNCTION;}
<INITIAL>var     {adjust(); return VAR;}
<INITIAL>type    {adjust(); return TYPE;}

    /*变量等 */
<INITIAL>[a-zA-Z][a-zA-Z0-9_]*   {adjust(); yylval.sval = String(yytext); return ID;}
<INITIAL>[0-9]+	 {adjust(); yylval.ival=atoi(yytext); return INT;}

<INITIAL>\"([^"\\]|(\\.))*\"    {adjust(); yylval.sval = String_strip(yytext); return STRING;}
    /*候补规则*/
<INITIAL>.	 {adjust(); EM_error(EM_tokPos,"illegal token");}




%%


int yywrap(void)
{
 charPos=1;
 return 1;
}


void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}