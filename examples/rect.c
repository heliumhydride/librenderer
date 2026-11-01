#define LIBRENDERER_NOPREFIX
#define LIBRENDERER_IMPLEMENTATION
#include "../librenderer.h"
#include <stdio.h>

int main(void)
{
    displaycontext_t d = initdisplay(40,40);
    clear_color_display(&d, 0xF9F9F9);
    drawrect(&d, 0xFFFF00, 10, 10, 10, 10, SHAPE_FILLED);
    drawcircle(&d, 0xFF0000, 20, 20, 5, SHAPE_FILLED);
    showdisplay(d);
    destroydisplay(&d);
    return 0;
}
