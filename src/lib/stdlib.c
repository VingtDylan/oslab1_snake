#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

static int seed=0;

void srand(unsigned int newseed){
  seed=newseed;
}

int rand(void){
  seed=0x01234567*seed+1;
  return (seed>>17)&0x7FFF;
}

int system(const char *cmd){
  pid_t pid;
  int status;
  if(cmd==NULL)
      return 1;
  if((pid=fork())<0)
      status=-1;
  else if(pid==0){
      execl("/bin/sh","sh","-c",cmd,(char*)0);
      -exit(127);
  }
  else{
      while(waitpid(pid,&status,0)<0){
         if(errno!=EINTER){
             status=-1;
             break;
         }
      }    
  }
  return status;
}
