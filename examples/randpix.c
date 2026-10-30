#define _XOPEN_SOURCE 500
#define LIBRENDERER_NOPREFIX
#define LIBRENDERER_IMPLEMENTATION
#include "../librenderer.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    puts("\033[7;33m/!\\ EPILESPY WARNING /!\\\033[0m");
    puts("You have 3 seconds to press CTRL+C");
    sleep(3);

    srand(time(NULL));
    displaycontext_t disp = initdisplay(40,40);

    for(size_t t = 0; t < disp.width*disp.height*2; ++t) {
        int x = rand() % disp.width;
        int y = rand() % disp.height;
        uint32_t color = rand() % 0x1000000;
        plotpixel(&disp, color, x, y);
        showdisplay(disp);
        usleep(1000);
    }

    destroydisplay(&disp);
    return 0;
}
