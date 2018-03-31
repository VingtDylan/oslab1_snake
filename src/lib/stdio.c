#include "stdarg.h"
#include "am.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

#define ZEROPAD 1
#define SIGN 2
#define PLUS 4
#define SPACE 8
#define LEFT 16
#define SPECIAL 32
#define LARGE 64

unsigned int write_int(char *buf,int val){
    unsigned char stack[10];
    unsigned char length=0;
    char *_tmp;
    if(val<0){
         *(buf++)='-';
         val*=-1;
    }
    do{
       stack[length]='0'+(val%10);
       val/=10;
       length++;
    }while(val);
   
    _tmp=itoa(length);
    while(length){
       *buf=stack[length-1];
       length--;
       buf++;
    }
    return buf-_tmp;
} 

int sprintf(char *buf,const char *fmt,...){
    va_list arg_ptr;
    //unsigned int buf_length=strlen(buf);
    unsigned int fmt_length=strlen(fmt);
    unsigned int index=0;
   
    int tmp;
    char ctmp;
    char* stmp;
  
    va_start(arg_ptr,fmt);
    for(index=0;index<fmt_length;++index){
       if(fmt[index]!='%')
           (*buf++)=fmt[index];
       else{
           switch(fmt[index+1]){
               case 'd': tmp=va_arg(arg_ptr,int);
                         buf=buf+write_int(buf,tmp);
                         break;
               case 's': stmp=(char *)va_arg(arg_ptr,char*);
                         strcpy(buf,stmp);
                         buf+=strlen(stmp);
                         break;
               case 'c': ctmp=va_arg(arg_ptr,int);
                         *(buf++)=ctmp;
                         break;
           } 
           index++;
       }
    }
    *buf=0;
    va_end(arg_ptr);
    return --index;
}

int snprintf(char *buf,size_t size,const char *fmt,...){
    va_list arg_ptr;
    //unsigned int buf_length=strlen(buf);
    unsigned int fmt_length=( strlen(fmt) > size ? size : strlen(fmt) );
    unsigned int index=0;
   
    int tmp;
    char ctmp;
    char* stmp;
  
    va_start(arg_ptr,fmt);
    for(index=0;index<fmt_length;++index){
       if(fmt[index]!='%')
           (*buf++)=fmt[index];
       else{
           switch(fmt[index+1]){
               case 'd': tmp=va_arg(arg_ptr,int);
                         buf=buf+write_int(buf,tmp);
                         break;
               case 's': stmp=(char *)va_arg(arg_ptr,char*);
                         strcpy(buf,stmp);
                         buf+=strlen(stmp);
                         break;
               case 'c': ctmp=va_arg(arg_ptr,int);
                         *(buf++)=ctmp;
                         break;
               case 'X':
               case 'x': 
                         break;
           } 
           index++;
       }
    }
    *buf=0;
    va_end(arg_ptr);
    return --index;    
}

void myitoa(int n,char str[],int radix){
   int i,j,rest;
   char tmp;
   i=0;
   do{
      rest=n%radix;
      if(rest>9) 
         str[i]=rest-10+'A';
      else
         str[i]=rest+'0';
      i++;
   }while(n/radix);
   str[i]='\0';
  
  for(i--,j=0;j<=i;j++,i--){
      tmp=str[j];
      str[j]=str[i];
      str[i]=tmp;
  }
}

void printch(const char ch){
    _putc(ch);
}

void printint(const int dec){
    if(dec==0)
        return ;
    printint(dec/10);
    _putc((char)(dec%10+'0'));
}

void printstr(const char *ptr){
    while(*ptr){
       _putc(*ptr);
       ptr++;
    }
}

void printfloat(const float flt){
    int tmpint =(int)flt;
    int tmpflt=(int)(100001*(flt-tmpint));
    if(tmpint%10>=5)
        tmpflt=tmpflt/10+1;
    else
        tmpflt=tmpflt/10;
    printint(tmpint);
    _putc('.');
    printint(tmpflt);
}

int printf(const char *fmt,... ){
    va_list ap;
    va_start(ap,fmt);
    while(*fmt){
       if(*fmt!='%'){
          _putc(*fmt);
          fmt++;
       }
       else{
          fmt++;
          switch(*fmt){
             case 'c': {
                          char valch=va_arg(ap,int);
                          printch(valch);
                          fmt++;   
                          break;
                       }
             case 'd': {
                          int valint=va_arg(ap,int);
                          printint(valint);
                          fmt++;
                          break;
                       }
             case 'X':
             case 'x': {
                          int fdval=va_arg(ap,int);
                          char str[30];
                          myitoa(fdval,str,16);
                          printint(fdval);
                          fmt++;
                          break;
                       }
             case 's': {
                          char *valstr=va_arg(ap,char*);
                          printstr(valstr);
                          fmt++;
                          break;
                       }
             case 'f': {  
                          float valflt=va_arg(ap,double);
                          printfloat(valflt);
                          fmt++;
                          break;
                       }
             default:  {  
                          printch(*fmt);
                          fmt++;
                       }
         }
      } 
    }
    return 0;  
}      





