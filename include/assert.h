#ifdef NDEBUG
  #define assert(ignore) ((void)0)
#else
  #define assert(cond) \
    do { \
      if (!(cond)){ \
         printf("Assertion fail at %s:%d\n",__FILE__,__LINE__); \
         _halt(1); \
      } \
    } while(0)
#endif
