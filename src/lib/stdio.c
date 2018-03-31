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



 #define ZEROPAD    1       /* pad with zero */
 #define SIGN   2       /* unsigned/signed long */
 #define PLUS   4       /* show plus */
 #define SPACE  8       /* space if plus */
 #define LEFT   16      /* left justified */
 #define SPECIAL    32      /* 0x */
 #define LARGE  64      /* use 'ABCDEF' instead of 'abcdef' */

 int _div(long* n,unsigned base)
 {
     int __res; 
         __res = ((unsigned long) *n) % (unsigned) base; 
         *n = ((unsigned long) *n) / (unsigned) base; 
         return __res;
 }

#define do_div(n,base) _div(&n,base)/*({ \
    int __res; \
    __res = ((unsigned long) n) % (unsigned) base; \
    n = ((unsigned long) n) / (unsigned) base; \
    __res; })*/




 static inline int isdigit(int ch)
 {
    return (ch >= '0') && (ch <= '9');
 }



 static int skip_atoi(const char **s)
 {
    int i = 0;

    while (isdigit(**s))
        i = i * 10 + *((*s)++) - '0';
    return i;
 }



 static char *Test_number(char *str, long num, int base, int size, int precision,
    int type)
 {
    char c, sign, tmp[66];
    const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    int i;

    if (type & LARGE)
        digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (type & LEFT)
        type &= ~ZEROPAD;
    if (base < 2 || base > 36)
        return 0;
    c = (type & ZEROPAD) ? '0' : ' ';
    sign = 0;
    if (type & SIGN) {
        if (num < 0) {
            sign = '-';
            num = -num;
            size--;
        } else if (type & PLUS) {
            sign = '+';
            size--;
        } else if (type & SPACE) {
            sign = ' ';
            size--;
        }
    }
    if (type & SPECIAL) {
        if (base == 16)
            size -= 2;
        else if (base == 8)
            size--;
    }
    i = 0;
    if (num == 0)
    {
        tmp[i++] = '0';
    }
    else
    {
        while (num != 0)
        {
            tmp[i++] = digits[do_div(num, base)];
        }
    }

    if (i > precision)
        precision = i;
    size -= precision;
    if (!(type & (ZEROPAD + LEFT)))
        while (size-- > 0)
            *str++ = ' ';
    if (sign)
        *str++ = sign;
    if (type & SPECIAL) {
        if (base == 8)
            *str++ = '0';
        else if (base == 16) {
            *str++ = '0';
            *str++ = digits[33];
        }
    }
    if (!(type & LEFT))
        while (size-- > 0)
            *str++ = c;
    while (i < precision--)
        *str++ = '0';
    while (i-- > 0)
        *str++ = tmp[i];
    while (size-- > 0)
        *str++ = ' ';
    return str;
 }




 int Test_vsprintf(char *buf, const char *fmt, va_list args)
 {
    int len;
    unsigned long num;
    int i, base;
    char *str;
    const char *s;

    int flags;      /* flags to Test_number() */

    int field_width;    /* width of output field */
    int precision;      /* min. # of digits for integers; max
                   Test_number of chars for from string */
    int qualifier;      /* 'h', 'l', or 'L' for integer fields */

    for (str = buf; *fmt; ++fmt) {
        if (*fmt != '%') {
            *str++ = *fmt;
            continue;
        }

        /* process flags */
        flags = 0;
          repeat:
        ++fmt;      /* this also skips first '%' */
        switch (*fmt) {
        case '-':
            flags |= LEFT;
            goto repeat;
        case '+':
            flags |= PLUS;
            goto repeat;
        case ' ':
            flags |= SPACE;
            goto repeat;
        case '#':
            flags |= SPECIAL;
            goto repeat;
        case '0':
            flags |= ZEROPAD;
            goto repeat;
        }

        /* get field width */
        field_width = -1;
        if (isdigit(*fmt))
            field_width = skip_atoi(&fmt);
        else if (*fmt == '*') {
            ++fmt;
            /* it's the next argument */
            field_width = Test_va_arg(args, int);
            if (field_width < 0) {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

        /* get the precision */
        precision = -1;
        if (*fmt == '.') {
            ++fmt;
            if (isdigit(*fmt))
                precision = skip_atoi(&fmt);
            else if (*fmt == '*') {
                ++fmt;
                /* it's the next argument */
                precision = Test_va_arg(args, int);
            }
            if (precision < 0)
                precision = 0;
        }

        /* get the conversion qualifier */
        qualifier = -1;
        if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
            qualifier = *fmt;
            ++fmt;
        }

        /* default base */
        base = 10;

        switch (*fmt) {
        case 'c':
            if (!(flags & LEFT))
                while (--field_width > 0)
                    *str++ = ' ';
            *str++ = (unsigned char)Test_va_arg(args, int);
            while (--field_width > 0)
                *str++ = ' ';
            continue;

        case 's':
            s = Test_va_arg(args, char *);
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
            if (field_width == -1) {
                field_width = 2 * sizeof(void *);
                flags |= ZEROPAD;
            }
            str = Test_number(str,
                     (unsigned long)Test_va_arg(args, void *), 16,
                     field_width, precision, flags);
            continue;

        case 'n':
            if (qualifier == 'l') {
                long *ip = Test_va_arg(args, long *);
                *ip = (str - buf);
            } else {
                int *ip = Test_va_arg(args, int *);
                *ip = (str - buf);
            }
            continue;

        case '%':
            *str++ = '%';
            continue;

            /* integer Test_number formats - set up the flags and "break" */
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
            num = Test_va_arg(args, unsigned long);
        else if (qualifier == 'h') {
            num = (unsigned short)Test_va_arg(args, int);
            if (flags & SIGN)
                num = (short)num;
        } else if (flags & SIGN)
            num = Test_va_arg(args, int);
        else
            num = Test_va_arg(args, unsigned int);
        str = Test_number(str, num, base, field_width, precision, flags);
    }
    *str = '\0';
    return str - buf;
}

int Test_printf(const char *fmt, ...)
{
    //定义接收输出信息最大长度1024字节
    char printf_buf[1024];

    //记录fmt对应的地址
    va_list args;
    int printed;
    //得到首个%对应的字符地址
    Test_va_start(args, fmt);
    printed = Test_vsprintf(printf_buf, fmt, args);
    Test_va_end(args);
    //输出到标准输出设备
    puts(printf_buf);

    return printed;
}
 

/*
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
*/





