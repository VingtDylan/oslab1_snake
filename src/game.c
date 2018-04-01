#include "game.h"
#include "stdio.h"
#include "lib.h"
#include "am.h"
#include "amdev.h"
#include "type.h"
#include "tool.h"

#define M  4  
#define maxn 256
#define maxlen 512
#define upper 1024

#define NONE                   "\033[m"   
#define RED                    "\033[0;32;31m"   
#define LIGHT_RED              "\033[1;31m"   
#define GREEN                  "\033[0;32;32m"   
#define LIGHT_GREEN            "\033[1;32m"   
#define BLUE                   "\033[0;32;34m"   
#define LIGHT_BLUE             "\033[1;34m"   
#define DARY_GRAY              "\033[1;30m"   
#define CYAN                   "\033[0;36m"   
#define LIGHT_CYAN             "\033[1;36m"   
#define PURPLE                 "\033[0;35m"   
#define LIGHT_PURPLE           "\033[1;35m"   
#define BROWN                  "\033[0;33m"   
#define YELLOW                 "\033[1;33m"   
#define LIGHT_GRAY             "\033[0;37m"   
#define WHITE                  "\033[1;37m"

#define HZ 100
#define FPS 30

#define darkgreen 0x00006400
#define firebrick 0x00b12222
#define deeppink  0x00cd1076

struct{
   int fps;
   int height,width;
   int next_frame;
}filefilm;

static int real_fps;
static int dida=0;

filefilm screen;

void timer(void){
  dida++;
}

void set_fps(int value){
  real_fps=value;
}

int get_fps(){
  return real_fps;
}

void init_screen(int fps){
  screen.fps=fps;
  screen.height=screen_width();
  screen.width=screen_height();
  screen.next_frame=0;
  printf("screen updated!");
}

void draw_screen(){
  //_VideoInfoReg info;
  //_Device *dev=_device(_DEV_VIDEO);
  _Device *dev=get_device(_DEV_VIDEO);
  //dev->read(_DEVREG_VIDEO_INFO,&info,sizeof(info));
  printf("have a test!\n");

  for(int x=0;x<100;x++)
     for(int y=0;y<100;y++){
         _FBCtlReg ctl;
         uint32_t pixels=0x00fa005f;
         ctl.x=x+screen.width/2;
         ctl.y=y+screen.height/2;
         ctl.w=ctl.h=1;
         ctl.sync=1;
         ctl.pixels=&pixels;
         dev->write(_DEVREG_VIDEO_FBCTL,&ctl,sizeof(ctl));
     } 
 
  /*uint32_t pixel=0x00ff0000;
  for(int x=0;x<100;x++)
    for(int y=0;y<100;y++)
       draw_rect(&pixel,x+info.width/2-50,y+info.height/2-50,1,1);
  */
}

void main_loop(){ 
      
   char str[M] = {0};  
   int i = 0;  
   char symbol[4] = {'|','/','-','\\'};  
   for(i = 0; i<M; ++i)  
   {  
       int c = i%5;  
       switch(c)  
       {  
           case 0:  
               printf(RED);  
               break;  
           case 1:  
               printf(GREEN);  
               break;  
           case 2:  
               printf(BLUE);  
               break;  
           case 3:  
               printf(YELLOW);  
               break;  
           case 4:  
               printf(BROWN);  
               break;  
       }  
 
       str[i] = '*';  
       /*if(system("clear")!=0)
          printf("clear!");*/  
       printf("[%-4s][%%%d][%c]",str,i*25,symbol[i%4]);  
       //fflush(stdout);  
       //sleep(1);  
       printf("\n");  
       /*if(system("clear")!=0)
          printf("clear!");*/  
   }  
   printf("\033[0m");
  
   static int fps=30;
   init_screen(fps);   
   
   draw_screen(); 
  
   /*int num_draw=0;
   int frames=0;
   int key;

   unsigned long next_frame=0;
   unsigned long next_refresh=0;

   while(1){
      bool fresh=false;
      while(uptime()<next_frame);
     
      //frames++; 
   
      if(uptime()>next_refresh){
           fresh=true;
           next_refresh+=1000/FPS;
      }
      //next_frame+=1000/FPS;
    
      while((key=read_key())!=_KEY_NONE){
         kbd_event(key);
      } 
   
      game_progress();

      if(fresh()){
         num_draw++;
         set_fps(num_draw*100/uptime());
         screen_update();
      }
      next_frame+=1000/FPS;
    }*/
    return ;
}



