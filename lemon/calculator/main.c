#include "util.h"
#include "calculator.h"
#include "parser.h"


extern void *ParseAlloc(void *(*mallocProc)(size_t));

extern void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  Token yyminor       /* The value for the token */
);


extern void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
);

int main(){
    FILE* f;
    f = fopen("record.txt","w");
    //ParseTrace(f,"");
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
    //z = (char*)malloc(1024);
    //char z[1024];
    char buf[1024];
    void* pParser = ParseAlloc(malloc);

    while(1){
        fgets(buf,1024,stdin);
        if(strcmp("q\n",buf)==0) break;
        //strcat(buf,"\n");
        //printf("z is [%s]\n",z);
        char* z =buf;
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