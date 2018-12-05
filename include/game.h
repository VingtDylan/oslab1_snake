#ifndef common_h
#define common_h

#define FPS 1000

//color
#define lightgrey 0x00d3d3d3
#define darkgreen 0x00006400
#define firebrick 0x00b12222
#define deeppink  0x00ff1493
#define magenta   0x00ff00ff
#define purple    0x006f005a

// direction
#define left  1
#define right 2
#define up    3
#define down  4

#include "stdio.h"
#include "lib.h"
#include "am.h"
#include "amdev.h"
#include "type.h"
#include "tool.h"
#include "time.h"

typedef enum{ false,true}bool;

//timer
void timer(void);
//initial
void init_screen();
void init_game();
//keyboard
void read_key(int *key,int *pressed);
void kbd_event(int ckey,int ckeydown);
//game logic
void generate();
void snake_move();
void get_food();
bool game_end();
void game_progress();
void screen_update();
void draw_screen();
void main_loop();

#endif
