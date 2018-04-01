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

#define black     0x00000000
#define darkgreen 0x00006400
#define firebrick 0x00b12222
#define deeppink  0x00cd1076

struct{
   int fps;
   int height,width;
   int next_frame;
}screen;

struct{
   int x[100];
   int y[100];
   int foods;
   int length;
   int speed;
   int direction;
   bool alive;
}snake;

struct{
   int fx;
   int fy;
}food[100];



static int real_fps;
static int dida=0;

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

void init_game(){
  snake.x[0]=snake.x[1]=1;
  snake.y[0]=snake.y[1]=0;
  snake.foods=0;
  snake.length=2;
  snake.speed=1;
  snake.alive=1;
}

void draw_screen(){
  uint32_t pixel=firebrick;
  for(int x=0;x<150;x++)
    for(int y=0;y<150;y++)
       draw_rect(&pixel,x+screen.width/2-50,y+screen.height/2-50,1,1);
}


void kbd_event(_KbdReg *key){
  
  //
  printf("in work\n");
}

void game_progress(){


  printf("to be completed\n");
}

void screen_update(){
  uint32_t backgroundcolor=black;
  uint32_t snakecolor=darkgreen;
  
  if(!snake.alive)
      backgroundcolor=firebrick;
 
  for(int i=0;i<screen.width;i++)
      for(int j=0;j<screen.height;j++){
         draw_rect(&backgroundcolor,i,j,1,1);
         for(int k=0;k<snake.length;k++){
              if(snake.x[k]==i&&snake.y[k]==j)
                   draw_rect(&snakecolor,i,j,1,1);
         }
      }
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
   init_game();      
   draw_screen();
   screen_update(); 
   //int num_draw=0;
   //int frames=0;
   
   //unsigned long next_frame=0;
   //unsigned long next_refresh=0;
   
   //while(1){
      //bool fresh=false;
     // while(uptime()<next_frame);
      //frames++; 
   
      //if(uptime()>next_refresh){
      //     fresh=true;
      //     next_refresh+=1000/FPS;
      //}
      //next_frame+=1000/FPS;
   
      //_KbdReg *key=read_key();
      //kbd_event(key); 
      //game_progress();
      
      //if(fresh){
        // num_draw++;
        // set_fps(num_draw*100/uptime());
      
     // screen_update();
     
      //}
      //next_frame+=1000/FPS;
   // }
    return ;
}



