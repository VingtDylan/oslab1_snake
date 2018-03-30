#include "am.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"
#include "stdlib.h"

char *itoa(int a){
   static char buf[30];
   char *p=buf+sizeof(buf);
   do{
        *--p='0'+a%10;
   }while(a/=10);
   return p;
}

void memcpy(void *dest,const void *src,size_t size){
  
}

void memset(void *dest,int data,size_t size){

}

size_t strlen(const char *str){
    int len=0;
    while(*str++)
        len++;
    return len;
}

void printch(const char ch){
    putchar(ch);
}

void printint(const int dec){
    if(dec==0)
        return ;
    printint(dec/10);
    putchar((char)(dec%10+'0'));
}

void printstr(const char *ptr){
    while(*ptr){
       putchar(*ptr);
       ptr++;
    }
}

void printfloat(const float flt){
    int tmpint =(int)flt;
    int tmpflt=(int)(100000*(flt-tmpint));
    if(tmpint%10>=5)
        tmpflt=tmpflt/10+1;
    else
        tmpflt=tmpflt/10;
    printint(tmpint);
    putchar('.');
    printint(tmpflt);
}

void printf(const char *fmt,... ){
    va_list ap;
    va_start(ap,fmt);
    while(*fmt){
       if(*fmt!='%'){
          putchar(*fmt);
          fmt++;
       }
       else{
          fmt++;
          switch(*fmt){
             case 'c': char valch=va_arg(ap,int);
                       printch(valch);
                       fmt++;   
                       break;
             case 'd': int valint=va_arg(ap,int);
                       printstr(valstr);
                       fmt++;
                       break;
             case 's': char *valstr=va_arg(ap,char*);
                       printstr(valstr);
                       fmt++;
                       break;
             case 'f': float valflt=va_arg(ap,double);
                       printfloat(valflt);
                       fmt++;
                       break;
             default:  printch(*fmt);
                       fmt++;
          }
       }
    }
    va_end(ap);
}



















