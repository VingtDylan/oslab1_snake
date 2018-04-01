#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "am.h"
#include "amdev.h"
#include "game.h"

/*
static uint32_t canvas[H][W];

extern char font8x8_basic[128][8];

static inline void draw_character(char ch,int x,int y,int color){
   int i,j;
   char *p=font8x8_basic[(int)(ch)];
   for(i=0;i<8;i++)
     for(j=0;j<8;j++)
       if((p[i]>>j)&1)
         if(x+j<W&&y+i<H)
            canvas[y+i][x+j]=color;
}

static inline void draw_string(const char *Str,int x,int y,int color){
   while(*str){
      draw_character(*str++,x,y,color);
      if(x+8>=W){
         y+=8;x=0;
      }else{
         x+=8;
      }
   }
}
*/
/*
void screen_update(){
   body_t it;
   food_t food;
   int i=0;

   for(it=snakebody();it!=NULL;it=it->next,i++){
      if(i==0)
          draw_string("O",it->r_x,it->r_y,9);
      else
          draw_string("*",it->r_x,it->r_y,10);
   }
   
   draw_string(itoa(i),0,200,14);
   draw_string("Length:",0,strlen("Length:")*8,33);
   
   food=getfood();
   
   if(food!=NULL)
          draw_string("#",food->x,food->y,4);
  
   draw_string(itoa(get_fps()),0,0,14);
   draw_string("FPS",0,strlen(itoa(get_fps()))*8,18);     
} 
*/
