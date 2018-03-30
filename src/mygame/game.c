#include "game.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "am.h"
#include "amdev.h"

#define HZ 100
#define FPS 30

typedef enum{
   false,
   true
}bool;

static int real_fps;

void set_fps(int value){
  real_fps=value;
}

int get_fps(){
  return real_fps;
}

void main_loop(){ 
   int num_draw=0;
   //int frames=0;
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
    }
    return 0;
}



