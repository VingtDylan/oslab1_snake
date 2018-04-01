#include "game.h"
#include "stdio.h"
#include "lib.h"
#include "am.h"
#include "amdev.h"
#include "type.h"
#include "tool.h"

//color
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

static int dida=0;
static int foo=0;
static int usedx,usedy;

bool foodflag;
bool gameflag;

void timer(void){
  dida++;
}

void init_screen(int fps){
  screen.fps=fps;
  screen.height=screen_height();
  screen.width=screen_width();
  screen.next_frame=0;
  printf("screen updated!");
}

void init_game(){
  snake.x[0]=screen.width/2;
  snake.y[0]=screen.height/2;
  snake.foods=0;
  snake.length=10;
  snake.speed=1;
  snake.direction=2;
  snake.alive=true;
  foodflag=false;
  gameflag=true;
  for(int i=1;i<snake.length;i++){
     snake.x[i]=snake.x[i-1]+1;
     snake.y[i]=snake.y[i-1];
  }
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
        case _KEY_UP:     {
                             if(snake.direction!=down)
                                   snake.direction=up;
                             printf("Up key!\b");     
                             break;
                          }
        case _KEY_DOWN:   {
                             if(snake.direction!=up)
                                   snake.direction=down;
                             printf("Down key!\n");   
                             break;
                          }
        case _KEY_LEFT:   {
                             if(snake.direction!=right)
                                   snake.direction=left;
                             printf("Left key!\n");   
                             break;
                          }
        case _KEY_RIGHT:  {
                             if(snake.direction!=left)
                                   snake.direction=right;
                             printf("Right key!\n"); 
                             break;
                          }
        case _KEY_Q:      {
                             gameflag=false;
                             printf("quit?\n");       
                             break;
                          }
        default:  break;
     }  
  }
}

void snake_move(){
  switch(snake.direction){
     case up:   {
                    snake.y[0]+=snake.speed;
                    break;
                }
     case down: {
                    snake.y[0]-=snake.speed;
                    break;
                }
     case left: {
                    snake.x[0]-=snake.speed;
                    break;
                }
     case right:{ 
                    snake.x[0]+=snake.speed;
                }
     default:break;
  } 
  usedx=snake.x[snake.length-1];
  usedy=snake.y[snake.length-1];
  for(int i=snake.length-1;i>=0;i--){
     snake.x[i]=snake.x[i-1];
     snake.y[i]=snake.y[i-1];
  }
}

void get_food(){
  if(snake.x[0]==food[foo].fx&&snake.y[0]==food[foo].fy){
     foodflag=false;
     snake.foods++;
     snake.x[snake.length]=usedx;
     snake.y[snake.length]=usedy;
     snake.length++;
  }  
  else
     return ;
}

bool game_end(){
     if(snake.x[0]<0||snake.x[0]>screen.width)
         gameflag=false;
     if(snake.y[0]<0||snake.y[0]>screen.height)
         gameflag=false;
     for(int i=1;i<snake.length;i++){
         if((snake.x[0]==snake.x[i])&&(snake.y[0]==snake.y[i])){
             gameflag=false; 
             printf("%d %d %d %d %d",i,snake.x[i],snake.x[0],snake.y[i],snake.y[0]);
         }
     }
     if(!gameflag)
         return true;
     return false;
}

void game_progress(){
  generate();
  snake_move();
  get_food();
}

void screen_update(){
  uint32_t backgroundcolor=0x00000000;//lightgrey;
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
         printf("%d",snake.length); 
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
   //printf("%d %d ",screen.height,screen.width); 
   //draw_screen();   
   //for(int i=0;i<snake.length;i++)
       //printf(" %d %d",snake.x[i],snake.y[i]);
   unsigned long  next_frame=0;
      
   while(1){
      while(uptime()<next_frame);
      //_KbdReg *key=read_key();
      //kbd_event(key); 
      game_progress();
      if(game_end())
          break;
      screen_update();
      next_frame+=1000/FPS;
    }
}



