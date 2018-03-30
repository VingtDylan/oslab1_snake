static int seed=0;

void srand(unsigned int newseed){
  seed=newseed;
}

int rand(void){
  seed=0x01234567*seed+1;
  return (seed>>17)&0x7FFF;
}

