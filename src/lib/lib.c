#include "unistd.h"
#include "stdio.h"
#include "assert.h"

static int seed=0;

void srand(unsigned int newseed){
  seed=newseed;
}

int rand(void){
  seed=0x01234567*seed+1;
  return (seed>>17)&0x7FFF;
}

char *itoa(int a){
   static char buf[30];
   char *p=buf+sizeof(buf);
   do{
        *--p='0'+a%10;
   }while(a/=10);
   return p;
}

void memcpy(char *dest,const char *src,size_t size){
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
  
}

void memset(void *dest,int data,size_t size){
   
}

size_t strlen(const char *str){
    int len=0;
    while(*str++)
        len++;
    return len;
}

char *strcpy(char *dest,const char *src){
    char *ret_val=dest;
    memcpy(dest,src,strlen(src)+1);
    return ret_val;
}

char *strncpy(char *dest,const char *src,size_t size){
    char *ret_val=dest;
    memcpy(dest,src,(strlen(src)>size?size:strlen(src))+1);
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
    else if(ret_val>0)
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
    else if(ret_val>0)
       return 1;
    return 0;
}

char *strchr(const char *s,int ch){
    if(s==NULL)
       return NULL;
    
    while(*s){
       if(*s==(char)ch)
           return (char *)s;
       s++;
    }
    return NULL; 
} 


