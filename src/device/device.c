#include <am.h>
#include <amdev.h>
#include <tool.h>
#include <lib.h>
#include <type.h>
#include <stdio.h>
#include <assert.h>

/*parameter
_DEV_PERFCNT 0x0000ac01
_DEV_INPUT   0x0000ac02
_DEV_TIMER   0x0000ac03
_DEV_VIDEO   0x0000ac04
_DEV_PCICONF 0x00000080
_DEV_ATA0    0x00000dd0
_DEV_ATA1    0x00000dd1
*/

static _Device *perfcnt = NULL;
static _Device *input = NULL;
static _Device *timer = NULL;
static _Device *video = NULL;
static _Device *pciconf = NULL;
static _Device *ata0=NULL;
static _Device *ata1=NULL;

_Device *get_device(uint32_t id) {
  for (int n = 1; ; n++){
    _Device *dev=_device(n);
    if(!dev)
      break;
    if (dev->id == id)
      return dev;
  }
  return NULL;
}

void init_perfcnt(){
  perfcnt=get_device(_DEV_PERFCNT);
}

void init_input(){
  input=get_device(_DEV_INPUT);
}

void init_timer(){
  timer=get_device(_DEV_TIMER);
}

void init_video(){
  video=get_device(_DEV_VIDEO);
}
 
void init_pciconf(){
  pciconf=get_device(_DEV_PCICONF);
}

void init_ata0(){
  ata0=get_device(_DEV_ATA0);
}

void init_ata1(){
  ata1=get_device(_DEV_ATA1);
}

uint32_t uptime() {
  if (!timer) 
    init_timer();

  _UptimeReg boottime;
  timer->read(_DEVREG_TIMER_UPTIME, &boottime, sizeof(boottime));
  return boottime.lo;
}

_KbdReg *read_key() {
  if (!input)
    init_input();

  _KbdReg *pressed=NULL;
  input->read(_DEVREG_INPUT_KBD, &pressed, sizeof(pressed));
  return pressed;
}

void draw_rect(uint32_t *pixels, int x, int y, int w, int h) {
  if (!video) 
    init_video();
  
  _FBCtlReg ctl;
  ctl.x = x;
  ctl.y = y;
  ctl.w = w;
  ctl.h = h;
  ctl.sync = 1;
  ctl.pixels =pixels;
  video->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(ctl));
}

void draw_sync() {
  // to be compledted
}

int screen_width() {
  if (!video) 
    init_video();

  _VideoInfoReg film;
  video->read(_DEVREG_VIDEO_INFO, &film, sizeof(film));
  return film.width;
}

int screen_height() {
  if (!video) 
    init_video();

  _VideoInfoReg film;
  video->read(_DEVREG_VIDEO_INFO, &film, sizeof(film));
  return film.height;
}

uint32_t read_pciconf(_Device *dev,uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
  if (!pciconf)
    init_pciconf();
  uint32_t res;
  dev->read(_DEVREG_PCICONF(bus,slot,func,offset),&res,4);
  return res;
}

uint8_t readb(_Device *dev,uint32_t reg){
  uint8_t res;
  dev->read(reg,&res,1);
  return res;
}

uint32_t readl(_Device *dev,uint32_t reg){
  uint32_t res;
  dev->read(reg,&res,4);
  return res;
}

void writeb(_Device *dev,uint32_t reg,uint8_t res){
  dev->write(reg,&res,1);
}

void read_disk(void *dst, int offset) {
  if (!ata0)
    init_ata0();

  while ((readb(ata0, _DEVREG_ATA_STATUS) & 0xc0) != 0x40);
  writeb(ata0, _DEVREG_ATA_NSECT,  1);
  writeb(ata0, _DEVREG_ATA_SECT,  offset);
  writeb(ata0, _DEVREG_ATA_CYLOW,  offset >> 8);
  writeb(ata0, _DEVREG_ATA_CYHIGH, offset >> 16);
  writeb(ata0, _DEVREG_ATA_DRIVE,  (offset >> 24) | 0xe0);
  writeb(ata0, _DEVREG_ATA_STATUS, 0x20);
  while ((readb(ata0, _DEVREG_ATA_STATUS) & 0xc0) != 0x40);
  for (int i = 0; i < SECTSZ / sizeof(uint32_t); i++) 
    ((uint32_t *)dst)[i] = readl(ata0, _DEVREG_ATA_DATA);
  printf("read completed!\n");
}
