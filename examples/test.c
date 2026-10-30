#define _XOPEN_SOURCE 500
#define LIBRENDERER_NOPREFIX
#define LIBRENDERER_IMPLEMENTATION
#include "../librenderer.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    displaycontext_t D = initdisplay(40,40);
    size_t x = 0;
    size_t y = 0;
    while(x < D.width) {
        drawline(&D, 0x88FF88, 0, D.height, D.width, 0);
        drawline(&D, 0xFF8888, 0, D.height/2, D.width, D.height/2);
        drawline(&D, 0x8888FF, D.width/2, 0, D.width/2, D.height);
        plotpixel(&D, 0xFF0066, x, y);
        showdisplay(D);

        usleep(1000000/20);
        resetdisplay(&D);
        y++; x++;
    }
    destroydisplay(&D);
    return 0;
}
