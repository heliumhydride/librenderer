#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
//#include <stdlib.h>
//#include <getopt.h>
//#include <unistd.h>
//#include <string.h>
#include "../librenderer.h"
#include "../util.h"

int main(void) {
  if(sodium_init() == -1) {
    fprintf(stderr, "sodium_init() failed\n");
    return 2;
  }

  char pixelmap[rows][cols];
  init_pxmap(pixelmap);

  printf("\033[s"); // save cursor position

  // TODO these lines segfault
  //mkline(pixelmap,15,58,4,15);
  //mkline(pixelmap,14,13,20,73);
  //mkline(pixelmap,5,29,11,66);
  //mkline(pixelmap,0,25,80,0);

  mkline(pixelmap,3,35,13,6);
  mkline(pixelmap,0,0,80,25);
  int a,b,c,d;
  while(1) {
    a = randint(1,rows-1); b = randint(1,cols-1);
    c = randint(1,rows-1); d = randint(1,cols-1);
    render_pixelmap(pixelmap);
    printf("\n\n    (%d;%d) -> (%d;%d)      \n",a,b,c,d);
    mkline(pixelmap,a,b,c,d);
    usleep(200000);
  }
  return 0;
}
