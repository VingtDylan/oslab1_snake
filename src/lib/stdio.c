#include "stdarg.h"
#include "am.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"


/*
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
*/

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

int is_flag(char ch){
   return strchr("0-+ #",ch)!=NULL;
}

int is_digit(char ch){
   return ('0'<=ch&&ch<='9');
}

int get_int(const char **fmt){
   int num=0;
   while(is_digit(**fmt)){
       num=num*10+(**fmt-'0');
       (*fmt)++;
   }
   return num;
}

void printch(const char ch){
    _putc(ch);
}

void printint(int num,int radix,int sign,char flag,int width,int precision){
    //precision to be completed
    static char digits[]="0123456789abcdef";
    char buffer[30];
   
    int negflag=0;
    uint32_t unum=num;
    if(sign&&num<0){
        negflag=1;
        unum=-num;
    }

    int i=0;
    do{
        buffer[i++]=digits[unum%radix];
    }while((unum/=radix)!=0);
   
    if(negflag)
        buffer[i++]='-';
  
    while(i<width)
        buffer[i++]=(flag=='0'?'0':' ');
   
    while(--i>=0)
        printch(buffer[i]);
}

void printstr(const char *ptr){
    while(*ptr){
       _putc(*ptr);
       ptr++;
    }
}

void intpt(const int n){
    if(n==0)
        return;
    intpt(n/10);
    _putc((char)(n%10+'0'));
}

void printfloat(const float flt){
    int tmpint =(int)flt;
    int tmpflt=(int)(100001*(flt-tmpint));
    if(tmpint%10>=5)
        tmpflt=tmpflt/10+1;
    else
        tmpflt=tmpflt/10;
    intpt(tmpint);
    _putc('.');
    intpt(tmpflt);
}

int printf(const char *fmt,... ){
    
    char flag='\0';
    int width=0;
    int precision=0;
   
    va_list ap;
    va_start(ap,fmt);

    while(*fmt){
       if(*fmt!='%'){
          _putc(*fmt);
          fmt++;
       }
       else{
          fmt++;
          //checkpoints
          if(is_flag(*fmt))
             flag=*fmt++;
          if(is_digit(*fmt))
             width=get_int(&fmt);
          
          switch(*fmt){
             case '%': _putc('%');break;
             case 'c': {
                          char valch=va_arg(ap,int);
                          printch(valch);
                          fmt++;   
                          break;
                       } 
             case 'D':
             case 'd': {
                          int valint=va_arg(ap,int);
                          printint(valint,10,1,flag,width,precision);
                          fmt++;
                          break;
                       }
             case 'X':
             case 'x': {
                          int fdval=va_arg(ap,int);
                          printint(fdval,16,0,flag,width,precision);
                          fmt++;
                          break;
                       }
             case 'O':
             case 'o': { 
                          int odval=va_arg(ap,int);
                          printint(odval,8,0,flag,width,precision);
                       }
             case 'S':
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





