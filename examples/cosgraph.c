#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

/// Useful includes
#include <stdio.h>
//#include <stdlib.h>
//#include <getopt.h>
//#include <unistd.h>
//#include <string.h>
#include <math.h>
#include "../librenderer.h"

int main(void) {
  char pixelmap[rows][cols];
  init_pxmap(pixelmap);

  printf("\033[s"); // save cursor position

  // TODO for every x from 0 to 'cols', graph the cos(x)

  add_pixel(pixelmap, 1,0,1.0f);
  render_pixelmap(pixelmap);

  /*
  for(int x = 0; x < cols; x++) {
    add_pixel(pixelmap, (int)(cos(x)*5), (int)rows/2, 1.0f);
    render_pixelmap(pixelmap);
  }
  */
  return 0;
}
