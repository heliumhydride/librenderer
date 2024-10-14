#define _POSIX_C_SOURCE 200112L

#include "librenderer.h"
// int cols; defined in config.h; default 80
// int rows; defined in config.h; default 25

void swap(int* a, int* b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

float fract_part(float x) {
  if(x > 0) return x - (int)x;
  else return x - ((int)x+1);
}

char opacity2ch(float opac) {
  // ._:-=+*n#%@
  if(opac <= 0.0f) {
    return ' ';
  } else if(opac > 0.0f && opac <= 0.1f) {
    return '.';
  } else if(opac > 0.1f && opac <= 0.2f) {
    return '_';
  } else if(opac > 0.2f && opac <= 0.3f) {
    return ':';
  } else if(opac > 0.3f && opac <= 0.4f) {
    return '-';
  } else if(opac > 0.4f && opac <= 0.5f) {
    return '=';
  } else if(opac > 0.5f && opac <= 0.6f) {
    return '+';
  } else if(opac > 0.6f && opac <= 0.7f) {
    return '*';
  } else if(opac > 0.7f && opac <= 0.8f) {
    return 'n';
  } else if(opac > 0.8f && opac <= 0.9f) {
    return '#';
  } else if(opac > 0.9f && opac < 1.0f) {
    return '%';
  } else if(opac >= 1.0f){
    return '@';
  }
  return '\0'; // default; should never run idealy
}

void add_pixel(char pxmap[rows][cols], int x, int y, float opac) {
  pxmap[x][y] = opacity2ch(opac);
}

void render_pixelmap(char pxmap[rows][cols]) {
  printf("\033[u"); // restore cursor position
  for(int i=0; i<rows; i++) {
    for(int j=0; j<cols; j++) {
      printf("%c", pxmap[i][j]);
    }
    printf("\n");
  }
}

void mkline(char pxmap[rows][cols], int x0, int y0, int x1, int y1) {
  int steep = abs(y1-y0) > abs(x1-x0);

  if(steep) {
    swap(&x0,&y0);
    swap(&x1,&y1);
  }
  if(x0 > x1) {
    swap(&x0,&x1);
    swap(&y0,&y1);
  }

  float dx = x1-x0;
  float dy = y1-y0;
  float m;
  if(dx == 0.0f)
    m = 1;
  else
    m = dy/dx;

  int xpxl1 = x0;
  int xpxl2 = x1;
  float intersect_y = y0;

  steep = 1;
  if(steep) {
    int x;
    for(x = xpxl1; x <= xpxl2; x++) {
      add_pixel(pxmap,
                (int)intersect_y, x,
                1 - fract_part(intersect_y)
               );
      add_pixel(pxmap,
                (int)intersect_y - 1, x,
                fract_part(intersect_y)
               );
      intersect_y += m;
    }
  } else { // not steep
    int x;
    for(x = xpxl1; x <= xpxl2; x++) {
      add_pixel(pxmap,
                x, (int)intersect_y,
                1 - fract_part(intersect_y)
               );
      add_pixel(pxmap,
                x, (int)intersect_y - 1,
                fract_part(intersect_y)
               );
      intersect_y += m;
    }
  }
}

void init_pxmap(char pxmap[rows][cols]) { // initialize pixelmap with spaces
  for(int i=0; i<rows; i++) {
    for(int j=0; j<cols; j++) {
      pxmap[i][j] = ' ';
    }
  }
}

