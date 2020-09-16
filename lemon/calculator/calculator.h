#include "util.h"

int getToken(const char* z, int *tokenType);
char* getstring(char* z, int n);
Symbol* symlook(char* s, Symbol* symtab);

void addfunc(char* name, double (*func)(double x), Symbol* symtab);
void addfunc2(char* name, double (*func)(double x,double y), Symbol* symtab);