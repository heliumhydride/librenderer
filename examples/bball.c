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

  int x_pos = 12; // set initial x position
  int y_pos = 40; // set initial y position
  int speed_x = randint(-3,3); // set initial horizontal speed
  int speed_y = randint(-3,3); // set initial vertical speed

  /* TODO draw initial ball here */
  add_pixel(pixelmap, x_pos, y_pos, 1.0);
  render_pixelmap(pixelmap);
  usleep(800000);

  while(1) {
    if(x_pos >= 0 || x_pos < cols || y_pos >= 0 || y_pos < rows)
      add_pixel(pixelmap, x_pos, y_pos, 0.0);
    x_pos += speed_x; y_pos += speed_y; // move
    if(x_pos >= 0 || x_pos < cols || y_pos >= 0 || y_pos < rows)
      add_pixel(pixelmap, x_pos, y_pos, 1.0);
    render_pixelmap(pixelmap);
    if(x_pos <= 0 || x_pos >= rows)
      speed_x = -speed_x; // bounce of the wall (horizontal) 
    if(y_pos <= 0 || y_pos >= cols)
      speed_y = -speed_y; // bounce of the wall (vertical) 
    usleep(30000);
  }
  return 0;
}
