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

#define lightgrey 0x00d3d3d3
#define darkgreen 0x00006400
#define firebrick 0x00b12222
#define deeppink  0x00ff1493

//direction
#define left  1
#define right 2
#define up    3
#define down  4

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
static int foo=0;

bool foodflag;

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
  screen.height=screen_height();
  screen.width=screen_width();
  screen.next_frame=0;
  printf("screen updated!");
}

void init_game(){
  snake.x[0]=screen.width/2;//=snake.x[1]=1;
  snake.y[0]=screen.height/2;//=snake.y[1]=0;
  snake.foods=0;
  snake.length=10;
  snake.speed=1;
  snake.direction=2;
  snake.alive=true;
  foodflag=false;
}

void generate(){
  if(foodflag)
      return ;
  food[foo].fx=rand()%(screen.width);
  food[foo].fy=rand()%(screen.height);
  foo++;
  foodflag=true;
}

void draw_screen(){
  uint32_t pixel=firebrick;
  for(int x=0;x<150;x++)
    for(int y=0;y<150;y++)
       draw_rect(&pixel,x+screen.width/2-50,y+screen.height/2-50,1,1);
}


void kbd_event(_KbdReg *key){
  if(key->keydown){
     switch(key->keycode){
        case _KEY_UP:     printf("Up key!\b");     break;
        case _KEY_DOWN:   printf("Down key!\n");   break;
        case _KEY_LEFT:   printf("Left key!\n");   break;
        case _KEY_RIGHT:  printf("Right key!\n");  break;
        case _KEY_Q:      printf("quit?\n");       break;
        default:  break;
     }  
  }
}

void game_progress(){
  generate();
  
  //printf("to be completed\n");
}

void screen_update(){
  uint32_t backgroundcolor=lightgrey;
  uint32_t snakecolor=darkgreen;
  uint32_t foodcolor=deeppink;
  if(!snake.alive)
      backgroundcolor=firebrick;
 
  for(int i=1;i<snake.length;i++){
      snake.x[i]=snake.x[i-1]+1;
      snake.y[i]=snake.y[i-1];
  }
  //printf("%d,%d",screen.width,screen.height);
  for(int i=0;i<screen.width;i++){
      for(int j=0;j<screen.height;j++){
         draw_rect(&backgroundcolor,i,j,1,1);
         //for(int k=0;k<snake.length;k++)
         //     printf("%d %d\n",snake.x[k],snake.y[k]);
          
         for(int k=0;k<snake.length;k++){
             if(snake.x[k]==i&&snake.y[k]==j){
                   draw_rect(&snakecolor,i,j,1,1);
                   //printf("body!\n");
             }
         }
         for(int k=0;k<=foo;k++){
             if(food[k].fx>=i&&food[k].fx<=i+4&&food[k].fy>=j&&food[k].fy<=j+4){
                  draw_rect(&foodcolor,i,j,1,1);
                  //printf("food!\n");
             }
         }
         
      }
  }
}


void main_loop(){ 
        
   static int fps=30;
   
   init_screen(fps);
   init_game();      
   //draw_screen();
    
   //int num_draw=0;
   //int frames=0;
   
   unsigned long next_frame=0;
   //unsigned long next_refresh=0;
   
   while(1){
      //bool fresh=false;
       while(uptime()<next_frame);
      //frames++; 
   
      //if(uptime()>next_refresh){
      //     fresh=true;
      //     next_refresh+=1000/FPS;
      //}
       next_frame+=1000/FPS;
   
       _KbdReg *key=read_key();
       kbd_event(key); 
       game_progress();
      
      //if(fresh){
        // num_draw++;
        // set_fps(num_draw*100/uptime());
      
       screen_update();
     
      
      next_frame+=1000/FPS;
    }
    return ;
}



