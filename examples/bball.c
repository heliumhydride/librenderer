#define _XOPEN_SOURCE 500
#define LIBRENDERER_NOPREFIX
#define LIBRENDERER_IMPLEMENTATION
#include "../librenderer.h"
#include <stdio.h>
#include <unistd.h>

#define START_POSITION_X 2
#define START_POSITION_Y 8
#define START_VELOCITY_X 2
#define START_VELOCITY_Y 1

int main(void)
{
    displaycontext_t d = initdisplay(40,40);

    int x = START_POSITION_X;
    int y = START_POSITION_Y;
    int vx = START_VELOCITY_X;
    int vy = START_VELOCITY_Y;

    for(size_t t = 0; t < 150; ++t) {
        plotpixel(&d, 0xFFFFFF, x, y);
        showdisplay(d);

        x += vx;
        y += vy;

        if(x < 0 || x >= (int)d.width) {
            x -= vx;
            vx = -vx; // we could be out of bounds, go back
        }
        if(y < 0 || y >= (int)d.height) {
            y -= vy;
            vy = -vy; // we could be out of bounds, go back
        }

        resetdisplay(&d);
        usleep(1000000/30);
    }

    destroydisplay(&d);
    return 0;
}
