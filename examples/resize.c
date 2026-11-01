#define _XOPEN_SOURCE 500
#define LIBRENDERER_NOPREFIX
#define LIBRENDERER_IMPLEMENTATION
#include "../librenderer.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    size_t width  = 10;
    size_t height = 10;
    displaycontext_t d = initdisplay(width,height);

    for(int i = 0; i < 60; ++i) {
        clear_color_display(&d, 0xFFFFFF);
        showdisplay(d);
        if(i < 30) {
            ++width;
            ++height;
        } else {
            --width;
            --height;
        }
        resizedisplay(&d, width, height);
        usleep(1000000/40);
    }

    destroydisplay(&d);
    return 0;
}
