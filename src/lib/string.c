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

char memcpy(char *dest,const char *src,size_t size){
   //asm volatile ("cld; rep movsb" : : "c"(size),"S"(src),"D"(dest));  
   //assert(dest!=NULL&&src==NULL);
   char *ret_val=dest;
   if(dest>=src&&dest<=src+size-1){
       dest=dest+size-1;
       src=src+size-1;
       while(size--)
           *dest--=*src--;
   }
   else{
       while(size--)
           *dest++=*src++;
   }
   //return ret_val
}

/*void memset(void *dest,int data,size_t size){
   asm volatile ("cld; rep stosb" : : "c"(size),"a"(data),"D"(dest));
}
*/

size_t strlen(const char *str){
    int len=0;
    while(*str++)
        len++;
    return len;
}

char *strcpy(char *dest,const char *src){
    //assert(dest!=NULL&&src!=NULL);
    char *ret_val=dest;
    memcpy(dest,src,strlen(src)+1);
    return ret_val;
}

char *strncpy(char *dest,const char *src,size_t size){
    char *ret_val=dest;
    memcpy(dest,src,(strlen(src)>size?size:strlen(src))+1;
    return ret_val;
}

int strcmp(const char *str1,const char *str2){
    int ret_val=0;
    while(!(ret_val=*(unsigned char *)str1-*(unsigned char *)str2)&&*str1){
       str1++;
       str2++;
    }
    if(ret_val<0)  
       return -1;
    else if(ret>0)
       return 1;
    return 0;
}  

int strncmp(const char *str1,const char *str2,size_t size){
    int ret_val=0;
    while(!(ret_val=*(unsigned char *)str1-*(unsigned char *)str2)&&*str1&&size){
       str1++;
       str2++;
       size--;
    }
    if(ret_val<0)  
       return -1;
    else if(ret>0)
       return 1;
    return 0;
}




















