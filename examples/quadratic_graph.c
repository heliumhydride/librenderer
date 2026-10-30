#define _XOPEN_SOURCE 500
#define LIBRENDERER_NOPREFIX
#define LIBRENDERER_IMPLEMENTATION
#include "../librenderer.h"
#include <stdio.h>
#include <unistd.h>

typedef struct {
    int x,y;
} Vec2i;

Vec2i central_coordinate(displaycontext_t d, float x, float y)
{
    return (Vec2i){
        .x = (x+1)/2*d.width,
        .y = (1 - (y+1)/2)*d.height
    };
}

float f(float x)
{
    return 1.5*x*x - 0.5; // 1.5x^2 - 0.5
}

int main(void)
{
    displaycontext_t d = initdisplay(40,40);

    drawline(&d, 0x303030, 0, d.height/2, d.width, d.height/2); // x-axis
    drawline(&d, 0x303030, d.width/2, 0, d.width/2, d.height); // y-axis

    // TODO ajust increment depending on width of screen
    float increment = 0.01f;
    for(float x = -1.0f; x < 1.0f; x+=increment) {
        Vec2i point = central_coordinate(d, x, f(x));
        plotpixel(&d, 0xFFFFFF, point.x, point.y);
        showdisplay(d);
        usleep(1000000/200);
    }

    destroydisplay(&d);
    return 0;
}
