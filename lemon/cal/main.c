
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NEWLINE 1
#define NUMBER 10

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

void token_desctructor(Token t){

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
}

static void addfunc2(char* name, double (*func)(double x,double y), Symbol* symtab)
{
    Symbol* sp = symlook(name, symtab);
    sp->funcptr2 = func;
}



int main(int argc, char const *argv[])
{
    /* code */
    FILE* f;
    f = fopen("record.txt","w");
    
}
