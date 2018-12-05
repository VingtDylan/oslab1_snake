#ifndef __STDIO_H__
#define __STDIO_H__

#include "am.h"

unsigned int write_inte(char *buf,int val);
int sprintf(char *buf,const char *fmt,...);
int snprintf(char *buf,size_t size,const char *fmt,...);
void myitoa(int n,char str[],int radix);
int is_flag(char ch);
int get_int(const char **fmt);
void printch(const char ch);
void printint(int num,int radix,int sign,char flag,int width,int precision);void printstr(const char *ptr);
void intpt(const int n);
void printfloat(const float flt);
int printf(const char* fmt,...);

#endif

