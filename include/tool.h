#ifndef __TOOL_H__
#define __TOOL_H__

#include <stdint.h>

#define SECTSZ 512

//deive
_Device *get_device(uint32_t id);
//initial
void init_perfcnt();
void init_input();
void init_timer();
void init_video();
void init_pciconf();
void init_ata0();
void init_ata1();
//main tools
uint32_t uptime();
void read_key(int *key,int*pressed);
void draw_rect(uint32_t *pixels, int x, int y, int w, int h);
void draw_sync();
int screen_width();
int screen_height();
//read aux
uint8_t readb(_Device *dev,uint32_t reg);
uint32_t readl(_Device *dev,uint32_t reg);
void writeb(_Device *dev,uint32_t reg,uint8_t res);
uint32_t read_pciconf(_Device *dev,uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
void read_disk(void *dest, int offset);

#endif
