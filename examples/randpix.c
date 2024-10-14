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

  while(1) {
    render_pixelmap(pixelmap);
    add_pixel(pixelmap, randint(0,rows), randint(0,cols), randfloat(0.0,1.0));
    usleep(20000);
  }
  return 0;
}
