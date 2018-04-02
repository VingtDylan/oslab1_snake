#include "game.h"
#include "stdio.h"
#include "lib.h"
#include "am.h"
#include "amdev.h"
#include "type.h"
#include "tool.h"
#include "time.h"

//color
#define lightgrey 0x00d3d3d3
#define darkgreen 0x00006400
#define firebrick 0x00b12222
#define deeppink  0x00ff1493
#define magenta   0x00ff00ff

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
   bool flag;
}food[100];

struct {
   int wx;
   int wy;
}wall[1000];

static int dida=0;
static int foo=0;
static int usedx,usedy;
static int wal=0;

bool foodflag;
bool gameflag;
bool game_win;

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
  game_win=false;
  for(int i=1;i<snake.length;i++){
     snake.x[i]=snake.x[i-1]-1;
     snake.y[i]=snake.y[i-1];
  }
}

void generate(){
  if(foodflag&&(dida%10!=0))
      return ;
  food[foo].fx=rand()%(screen.width);
  food[foo].fy=rand()%(screen.height);
  food[foo].flag=true;
  foo++;
  foodflag=true;
  if(foo==10)
      game_win=true;
  
  if(dida%10!=0)
      return ;
  wall[wal].wx=rand()%(screen.width);
  wall[wal].wy=rand()%(screen.height);
  wal+=20;
  if(wal<=1000)
      for(int i=wal-19;i<wal;i++){
          wall[i].wx=wall[i-1].wx+1;
          wall[i].wy=wall[i-1].wy;
      }
}

void draw_screen(){
  uint32_t pixel=firebrick;
  for(int x=0;x<150;x++)
    for(int y=0;y<150;y++)
       draw_rect(&pixel,x+screen.width/2-50,y+screen.height/2-50,1,1);
}

//static int n=0;
//static int index=0;

void kbd_event(int ckey,int ckeydown){
  
  /*key->keydown=1;
  key->keycode=n%4+73;
  switch(index){
     case 0:
     case 1:n=2;break;
     case 2:
     case 3:n=0;break;
     case 4:
     case 5:n=3;break;
     case 6:
     case 7:n=0;break;
  }
  index=(index+1)%8;*/
  //printf("%d %d %d ",_KEY_DOWN,_KEY_LEFT,_KEY_RIGHT);
  if(ckeydown){
     switch(ckey){
        case 73:     {  //_KEY_UP
                             if(snake.direction!=down)
                                   snake.direction=up;
                             printf("Up key!\n");     
                             break;
                          }
        case 74:   {  //_KEY_DOWN
                             if(snake.direction!=up)
                                   snake.direction=down;
                             printf("Down key!\n");   
                             break;
                          }
        case 75:  {  //_KEY_LEFT
                             if(snake.direction!=right)
                                   snake.direction=left;
                             printf("Left key!\n");   
                             break;
                          }
        case 76:  {  //_KEY_RIGHT
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
  usedx=snake.x[snake.length-1];
  usedy=snake.y[snake.length-1];
  for(int i=snake.length-1;i>=1;i--){
     snake.x[i]=snake.x[i-1];
     snake.y[i]=snake.y[i-1];
  }
  switch(snake.direction){
     case up:   {
                    snake.y[0]-=snake.speed*4;
                    break;
                }
     case down: {
                    snake.y[0]+=snake.speed*4;
                    break;
                }
     case left: {
                    snake.x[0]-=snake.speed*4;
                    break;
                }
     case right:{ 
                    snake.x[0]+=snake.speed*4;
                }
     default:break;
  } 

}

void get_food(){
  for(int i=0;i<foo;i++){
     if(snake.x[0]==food[i].fx&&snake.y[0]==food[i].fy){
          food[i].flag=false;
          snake.foods++;
          if(snake.foods>=20)
              game_win=true;
          snake.x[snake.length]=usedx;
          snake.y[snake.length]=usedy;
          snake.length++;
          foodflag=false;
          for(int j=i;j<foo;j++){ 
             food[j].fx=food[j+1].fx;
             food[j].fy=food[j+1].fy;
             food[j].flag=food[j+1].flag;
          }
          foo--;
          for(int j=0;j<=foo;j++)
             if(food[j].flag)
                 foodflag=true;
     } 
  } 
  return ;
}

bool game_end(){
     if(snake.x[0]<0||snake.x[0]>screen.width)
         gameflag=false;
     if(snake.y[0]<0||snake.y[0]>screen.height)
         gameflag=false;
     for(int i=0;i<wal;i++){
         if(snake.x[0]==wall[i].wx&&snake.y[0]==wall[i].wy)
             gameflag=false;
     }
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
  uint32_t backgroundcolor=lightgrey;
  uint32_t snakecolor=darkgreen;
  uint32_t foodcolor=deeppink;
  uint32_t wallcolor=magenta;

  if(!snake.alive)
      backgroundcolor=firebrick;
 
  for(int i=0;i<screen.width;i++){
      for(int j=0;j<screen.height;j++){
         draw_rect(&backgroundcolor,i,j,1,1);
         for(int k=0;k<snake.length;k++){
             if(snake.x[k]>=i&&snake.x[k]<=i+4&&snake.y[k]>=j&&snake.y[k]<=j+4){
                   draw_rect(&snakecolor,i,j,1,1);
                   //printf("body!\n");
             }
         }
         for(int k=0;k<=foo;k++){
             if(food[k].fx>=i&&food[k].fx<=i+4&&food[k].fy>=j&&food[k].fy<=j+4){
                  draw_rect(&foodcolor,i,j,1,1);
             }
         }
         for(int k=0;k<wal;k++){
             if(wall[k].wx>=i&&wall[k].wx<=i+4&&wall[k].wy>=j&&wall[k].wy<=j+4)
                  draw_rect(&wallcolor,i,j,1,1);
         }
      }
  }
}


void main_loop(){ 
   static int fps=30;
   init_screen(fps);
   init_game();     
   //draw_screen();   
   unsigned long  next_frame=0;
      
   while(1){
      while(uptime()<next_frame); 
      timer();
      int key,pressed;
      read_key(&key,&pressed);
      kbd_event(key,pressed);
      game_progress();
      //if(game_end())
          //break;
      if(game_win)
          break;
      screen_update();
      next_frame+=1000/FPS;
    }
}



