#ifndef __LIB_H__
#define __LIB_H__

#include "am.h"

void srand(unsigned int seed);
int rand();
char *itoa(int);
void  memcpy(char *,const char *,size_t);
void  memset(char *,int,size_t);
size_t strlen(const char *);
char *strcpy(char *dest,const char *src);
char *strncpy(char *dest,const char *Src,size_t size);
int strcmp(const char *str1,const char *str2);
int strncmp(const char *str1,const char *str2,size_t size);
char *strchr(const char *s,int ch);

#endif
