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

  for(int x = 0; x < cols; x++) {
    add_pixel(pixelmap, (int)(rows/2 + cos(x)*1.1), x, 1.0f);
    render_pixelmap(pixelmap);
  }
  return 0;
}
