#include "stdarg.h"
#include "am.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

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
           } 
           index++;
       }
    }
    *buf=0;
    va_end(arg_ptr);
    return --index;    
}

/*
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
    va_end(ap);
    return 0;
}
*/

int vsprintf(char *buf, const char *fmt, va_list args)
{
    int len;
    unsigned long long num;
    int i, base;
    char * str;
    const char *s;

    int flags;        

    int field_width;    
    int precision;       
    int qualifier;       

    for (str=buf ; *fmt ; ++fmt)
    {
        if (*fmt != '%') 
        {
            *str++ = *fmt;
            continue;
        }
        flags = 0;
        repeat:
            ++fmt;      
            switch (*fmt)
            {
                case '-': flags |= LEFT; goto repeat;
                case '+': flags |= PLUS; goto repeat;
                case ' ': flags |= SPACE; goto repeat;
                case '#': flags |= SPECIAL; goto repeat;
                case '0': flags |= ZEROPAD; goto repeat;
            }

        field_width = -1;
        if ('0' <= *fmt && *fmt <= '9')
            field_width = skip_atoi(&fmt);
        else if (*fmt == '*')
        {
            ++fmt;
            field_width = va_arg(args, int);
            if (field_width < 0) {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

 
        precision = -1;
        if (*fmt == '.')
        {
            ++fmt;   
            if ('0' <= *fmt && *fmt <= '9')
                precision = skip_atoi(&fmt);
            else if (*fmt == '*')
            {
                ++fmt;

                precision = va_arg(args, int);
            }
            if (precision < 0)
                precision = 0;
        }

        qualifier = -1;
        if (*fmt == 'l' && *(fmt + 1) == 'l')
        {
            qualifier = 'q';
            fmt += 2;
        }
        else if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L'|| *fmt == 'Z')
        {
            qualifier = *fmt;
            ++fmt;
        }

        base = 10;
   
        switch (*fmt)
        {
            case 'c':
                if (!(flags & LEFT))
                    while (--field_width > 0)
                    *str++ = ' ';
                    *str++ = (unsigned char) va_arg(args, int);
                    while (--field_width > 0)
                    *str++ = ' ';
                    continue;

            case 's':
                s = va_arg(args, char *);
                if (!s)
                    s = "";

                    len = strnlen(s, precision);

                    if (!(flags & LEFT))
                    while (len < field_width--)
                    *str++ = ' ';
                    for (i = 0; i < len; ++i)
                    *str++ = *s++;
                    while (len < field_width--)
                    *str++ = ' ';
                    continue;
            case 'p':
                if (field_width == -1)
                {
                    field_width = 2*sizeof(void *);
                    flags |= ZEROPAD;
                }
                str = number(str,(unsigned long) va_arg(args, void *), 16,
                        field_width, precision, flags);
                continue;

            case 'n':
            if (qualifier == 'l')
            {
                long * ip = va_arg(args, long *);
                *ip = (str - buf);
            }
            else if (qualifier == 'Z')
            {
                size_t * ip = va_arg(args, size_t *);
                *ip = (str - buf);
            }
            else
            {
                int * ip = va_arg(args, int *);
                *ip = (str - buf);
            }
            continue;
            case '%':
            *str++ = '%';
            continue;

            case 'o':
            base = 8;
            break;

            case 'X':
            flags |= LARGE;
            case 'x':
            base = 16;
            break;
            case 'd':
            case 'i':
            flags |= SIGN;
            case 'u':
            break;

            default:
            *str++ = '%';
            if (*fmt)
                *str++ = *fmt;
            else
                --fmt;
            continue;
        }

        if (qualifier == 'l')
        {
            num = va_arg(args, unsigned long);
            if (flags & SIGN)
                num = (signed long) num;
        }
        else if (qualifier == 'q')
        {
            num = va_arg(args, unsigned long long);
            if (flags & SIGN)
                num = (signed long long) num;
        }
        else if (qualifier == 'Z')
        {
            num = va_arg(args, size_t);
        }
        else if (qualifier == 'h')
        {
            num = (unsigned short) va_arg(args, int);
            if (flags & SIGN)
                num = (signed short) num;
        }
        else
        {
            num = va_arg(args, unsigned int);
            if (flags & SIGN)
                num = (signed int) num;
        }
        str = number(str, num, base, field_width, precision, flags);
    }
    *str = '/0';
    return str-buf;
}


int printf(const char *fmt, ...)
{
    va_list args;
    int n;
    va_start(args, fmt);
    n = vsprintf(sprint_buf, fmt, args);
    va_end(args);
    if (console_ops.write)
        console_ops.write(sprint_buf, n);
    return n;
}
























