/*

    librenderer

    see README.md

    made with ♡ by heliumhydride

*/

#ifndef _LIBRENDERER_H
#define _LIBRENDERER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} librenderer_pixel_t;

typedef struct {
    size_t width, height;
    librenderer_pixel_t* data;
} librenderer_displaycontext_t;

typedef enum {
    LIBRENDERER_SHAPE_FILLED,
    LIBRENDERER_SHAPE_EMPTY
} librenderer_shape_style;

librenderer_displaycontext_t librenderer_initdisplay(size_t width, size_t height);
void librenderer_showdisplay(librenderer_displaycontext_t display);
void librenderer_plotpixel(librenderer_displaycontext_t* dp, uint32_t color, int x, int y);
void librenderer_destroydisplay(librenderer_displaycontext_t* dp);
void librenderer_resetdisplay(librenderer_displaycontext_t* dp);
void librenderer_clear_color_display(librenderer_displaycontext_t* dp, uint32_t color);
void librenderer_helper_swapi(int* a, int* b);
int librenderer_helper_absi(int a);
void librenderer_drawline(librenderer_displaycontext_t* dp, uint32_t color, int x0, int y0, int x1, int y1);
void librenderer_resizedisplay(librenderer_displaycontext_t* dp, size_t width, size_t height);
void librenderer_drawrect(librenderer_displaycontext_t* dp, uint32_t color, int x, int y, unsigned int width, unsigned int height, librenderer_shape_style style);
void librenderer_drawcircle(librenderer_displaycontext_t* dp, uint32_t color, int x, int y, int radius, librenderer_shape_style style);

#ifdef LIBRENDERER_NOPREFIX
#define displaycontext_t   librenderer_displaycontext_t
#define pixel_t            librenderer_pixel_t
#define initdisplay        librenderer_initdisplay
#define destroydisplay     librenderer_destroydisplay
#define showdisplay        librenderer_showdisplay
#define plotpixel          librenderer_plotpixel
#define resetdisplay       librenderer_resetdisplay
#define clear_color_display librenderer_clear_color_display
#define helper_swapi       librenderer_helper_swapi
#define helper_absi        librenderer_helper_absi
#define drawline           librenderer_drawline
#define resizedisplay      librenderer_resizedisplay
#define drawrect           librenderer_drawrect
#define drawcircle         librenderer_drawcircle
#define SHAPE_FILLED       LIBRENDERER_SHAPE_FILLED
#define SHAPE_EMPTY        LIBRENDERER_SHAPE_EMPTY
#endif // LIBRENDERER_NOPREFIX

#ifndef LIBRENDERER_GRAYSCALE_THRESHOLD
#define LIBRENDERER_GRAYSCALE_THRESHOLD 40
#endif

#ifdef LIBRENDERER_NO_UTF8
    #define UPPER_HALF_BLOCK   "^"
    #define LOWER_HALF_BLOCK   "_"
    #define FULL_BLOCK         "@"
    #define VERTICAL_BAR       "|"
    #define HORIZONTAL_BAR     "-"
    #define LOWER_LEFT_CORNER  "\\"
    #define LOWER_RIGHT_CORNER "/"
    #define UPPER_LEFT_CORNER  "/"
    #define UPPER_RIGHT_CORNER "\\"
#else
    #define UPPER_HALF_BLOCK   "\xe2\x96\x80"
    #define LOWER_HALF_BLOCK   "\xe2\x96\x84"
    #define FULL_BLOCK         "\xe2\x96\x88"
    #define VERTICAL_BAR       "\xe2\x94\x82"
    #define HORIZONTAL_BAR     "\xe2\x94\x80"
    #define LOWER_LEFT_CORNER  "\xe2\x94\x94"
    #define LOWER_RIGHT_CORNER "\xe2\x94\x98"
    #define UPPER_LEFT_CORNER  "\xe2\x94\x8c"
    #define UPPER_RIGHT_CORNER "\xe2\x94\x90"
#endif // NO_UTF8


#ifdef LIBRENDERER_IMPLEMENTATION

#define __TODO(msg)   do { fprintf(stderr, "%s: %d: \033[7;33mTODO\033[0m   %s\n", __FILE__, __LINE__, (msg)); abort(); } while(0)
#define __ERROR(msg)   do { fprintf(stderr, "%s: %d: \033[1;31mERROR\033[0m   %s\n", __FILE__, __LINE__, (msg)); abort(); } while(0)

librenderer_displaycontext_t librenderer_initdisplay(size_t width, size_t height)
{
    size_t size = width * height * sizeof(librenderer_pixel_t);
    librenderer_pixel_t* data = malloc(size);
    if(data == NULL)
        __ERROR("could not allocate sufficient memory for display");

    return (librenderer_displaycontext_t){
        .width  = width,
        .height = height,
        .data   = memset(data, 0, size)
    };
}

void librenderer_showdisplay(librenderer_displaycontext_t display)
{
    printf("\033[H\033[J" UPPER_LEFT_CORNER);
    for(size_t i = 0; i < display.width; ++i) printf(HORIZONTAL_BAR);
    printf(UPPER_RIGHT_CORNER "\n");

    for(size_t y = 0; y < display.height; y+=2) {
        printf(VERTICAL_BAR);
        for(size_t x = 0; x < display.width; ++x) {
            librenderer_pixel_t pixel1 = display.data[y*display.width + x];
            librenderer_pixel_t pixel2 = display.data[(y+1)*display.width + x];

            #ifdef LIBRENDERER_NOCOLOR
            uint8_t pixel1_gray = (uint8_t)(0.2126*(float)pixel1.r + 0.7152*(float)pixel1.g + 0.0722*(float)pixel1.b);
            uint8_t pixel2_gray = (uint8_t)(0.2126*(float)pixel2.r + 0.7152*(float)pixel2.g + 0.0722*(float)pixel2.b);

            uint8_t char_state = (pixel1_gray > LIBRENDERER_GRAYSCALE_THRESHOLD) << 1 | (pixel2_gray > LIBRENDERER_GRAYSCALE_THRESHOLD);
            switch(char_state) {
                case 0: // 0b00
                    putchar(' ');
                    break;
                case 1: // 0b01
                    printf(LOWER_HALF_BLOCK);
                    break;
                case 2: // 0b10
                    printf(UPPER_HALF_BLOCK);
                    break;
                case 3: // 0b11
                    printf(FULL_BLOCK);
                    break;
            }
            #else // We have true-color support
            // set text background color to pixel 1 color
            printf("\033[48;2;%d;%d;%dm", pixel1.r, pixel1.g, pixel1.b);
            // set text foreground color to pixel 2 color
            printf("\033[38;2;%d;%d;%dm", pixel2.r, pixel2.g, pixel2.b);
            printf(LOWER_HALF_BLOCK);
            #endif // LIBRENDERER_NOCOLOR
        }
        printf("\033[0m"VERTICAL_BAR"\n");
    }

    printf(LOWER_LEFT_CORNER);
    for(size_t i = 0; i < display.width; ++i) printf(HORIZONTAL_BAR);
    printf(LOWER_RIGHT_CORNER "\n");
}

void librenderer_plotpixel(librenderer_displaycontext_t* dp, uint32_t color, int x, int y)
{
    if(x < 0) return;
    if(y < 0) return;
    if(x > (int)dp->width) return;
    if(y > (int)dp->height) return;
    uint8_t r = (color & 0x00FF0000) >> 16;
    uint8_t g = (color & 0x0000FF00) >> 8;
    uint8_t b = color & 0x000000FF;
    dp->data[y * dp->width + x] = (pixel_t){r,g,b};
}

void librenderer_resetdisplay(librenderer_displaycontext_t* dp)
{
    memset(dp->data, 0, dp->width * dp->height * sizeof(librenderer_pixel_t));
}

void librenderer_clear_color_display(librenderer_displaycontext_t* dp, uint32_t color) {
    for(size_t x = 0; x < dp->width; ++x) {
        for(size_t y = 0; y < dp->height; ++y) {
            librenderer_plotpixel(dp, color, x, y);
        }
    }
}

void librenderer_helper_swapi(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int librenderer_helper_absi(int a)
{
    if(a < 0) return -a;
    return a;
}

void librenderer_drawline(librenderer_displaycontext_t* dp, uint32_t color, int x0, int y0, int x1, int y1)
{
    int steep = librenderer_helper_absi(y1 - y0) > librenderer_helper_absi(x1 - x0);
    if(steep) {
        librenderer_helper_swapi(&x0, &y0);
        librenderer_helper_swapi(&x1, &y1);
    }

    if (x0 > x1) {
        librenderer_helper_swapi(&x0, &x1);
        librenderer_helper_swapi(&y0, &y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    float slope = (float)dy/(float)dx;
    if(dx == 0) slope = 1;
    
    if(steep) {
        for(int x = x0; x < x1; ++x) {
            int y = (int)(slope * (float)(x-x0) + (float)y0);
            librenderer_plotpixel(dp, color, y, x);
        }
    } else {
        for(int x = x0; x < x1; ++x) {
            int y = (int)(slope * (float)(x-x0) + (float)y0);
            librenderer_plotpixel(dp, color, x, y);
        }
    }
}

void librenderer_destroydisplay(librenderer_displaycontext_t* dp)
{
    free(dp->data);
}

void librenderer_resizedisplay(librenderer_displaycontext_t* dp, size_t width, size_t height)
{
    dp->width = width;
    dp->height = height;
    dp->data = realloc(dp->data, width * height * sizeof(librenderer_pixel_t));
    if(dp->data == NULL)
        __ERROR("could not allocate sufficient memory for to resize display");
}

void librenderer_drawrect(librenderer_displaycontext_t* dp, uint32_t color, int x, int y, unsigned int width, unsigned int height, librenderer_shape_style style) {
    librenderer_drawline(dp, color, x, y, x+width, y);
    librenderer_drawline(dp, color, x, y+height, x+width+1, y+height);
    librenderer_drawline(dp, color, x, y, x, y+height);
    librenderer_drawline(dp, color, x+width, y, x+width, y+height);
    if(style == LIBRENDERER_SHAPE_FILLED) {
        for(int i = 0; i < (signed)width; ++i)
            librenderer_drawline(dp, color, x+i, y, x+i, y+height);
    }
}

void librenderer_drawcircle(librenderer_displaycontext_t* dp, uint32_t color, int x, int y, int radius, librenderer_shape_style style) {
    int radius_squared = radius * radius;
    for(int x_i = -radius; x_i < radius; ++x_i) {
        for(int y_i = -radius; y_i < radius; ++y_i) {
            switch(style) {
                case LIBRENDERER_SHAPE_FILLED:
                    if((x_i*x_i + y_i*y_i) < radius_squared)
                        librenderer_plotpixel(dp, color, x+x_i, y+y_i);
                    break;
                case LIBRENDERER_SHAPE_EMPTY:
                    if((x_i*x_i + y_i*y_i) == radius_squared)
                        librenderer_plotpixel(dp, color, x+x_i, y+y_i);
                    break;
            }
        }
    }
}

#endif // LIBRENDERER_IMPLEMENTATION
#endif // _LIBRENDERER_H
