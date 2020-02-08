/*
 * util.c - commonly used utility functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
void *checked_malloc(int len)
{void *p = malloc(len);
 if (!p) {
    fprintf(stderr,"\nRan out of memory!\n");
    exit(1);
 }
 return p;
}


/* 将字符串char* s 复制到一个新分配的字符串p中
*/
string String(char *s)
{string p = checked_malloc(strlen(s)+1);
 strcpy(p,s);
 return p;
}

string String_strip(char *s)
{
   int len = strlen(s);
   string p = checked_malloc(len - 1);
   p[len-2] = '\0';
   int i;
   for(i=0; i<len-2;i++){
      p[i]=s[i+1];
   }
   return p;
   
}

U_boolList U_BoolList(bool head, U_boolList tail)
{ U_boolList list = checked_malloc(sizeof(*list));
  list->head = head;
  list->tail = tail;
  return list;
}