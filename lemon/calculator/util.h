
#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>


#define NUMBER 20

//一些类型定义
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

#endif