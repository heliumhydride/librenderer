#define LIBRENDERER_NOPREFIX
#define LIBRENDERER_IMPLEMENTATION
#include "../librenderer.h"
#include <stdio.h>

int main(void)
{
    displaycontext_t d = initdisplay(40,40);
    drawrect(&d, 0x909090, 10, 10, 20, 20, RECT_FILLED);
    showdisplay(d);
    destroydisplay(&d);
    return 0;
}
