#include <am.h>
#include <amdev.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <game.h>
#include <type.h>

int main() {
  
  if (_ioe_init() != 0) 
      _halt(1);

  main_loop();
  return 0;
} 

