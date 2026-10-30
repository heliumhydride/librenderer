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
    while(1) {
        plotpixel(&D, 0xFF00FF, x, y);
        drawline(&D, 0x50FF50, 0, D.height, D.width, 0);
        drawline(&D, 0x50FF50, 0, D.height/2, D.width, D.height/2);
        drawline(&D, 0x50FF50, D.width/2, 0, D.width/2, D.height);
        showdisplay(D);

        usleep(1000000/15);
        resetdisplay(&D);
        y++; x++;
    }
    destroydisplay(&D);
    return 0;
}
