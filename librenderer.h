#ifndef LIBRENDERER_H
#define LIBRENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdint.h>

#include "config.h"

void swap(int* a, int* b);
float fract_part(float x);
char opacity2ch(float opac);
void add_pixel(char pxmap[rows][cols], int x, int y, float opac);
void render_pixelmap(char pxmap[rows][cols]);
void mkline(char pxmap[rows][cols], int x0, int y0, int x1, int y1);
void init_pxmap(char pxmap[rows][cols]);

#endif
