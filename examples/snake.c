#define _XOPEN_SOURCE   600
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
//#include <stdlib.h>
//#include <getopt.h>
//#include <unistd.h>
//#include <string.h>

#include <sodium.h>
#include "../librenderer.h"

int main(void) {
  if(sodium_init() == -1) {
    fprintf(stderr, "sodium_init() failed\n");
    return 2;
  }

  char pixelmap[rows][cols];
  init_pxmap(pixelmap);

  printf("\033[s"); // save cursor position for render_pixelmap()

  int player_x = 0;
  int player_y = 0;
  int game_done = 0;
  int score = 0;

  // draw walls
  // TODO segfaults, need to fix mkline() first
  mkline(pixelmap, 0,      0,      cols-1, 0);
  mkline(pixelmap, 0,      0,      0,      rows-1);
  mkline(pixelmap, 0,      rows-1, cols-1, rows-1);
  mkline(pixelmap, cols-1, 0,      cols-1, rows-1);

  while(!game_done) { // game loop
    render_pixelmap(pixelmap);
    if(0) // will be replaced with a condition of whenever the player collides with the walls or itself
      game_done = 1;
    usleep(10000); // could be made variable, to change game speed for something like difficulty for example
  }
  
  printf("\n\n  Game over! score was %d\n", score);
  return 0;
}
