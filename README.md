# 🖌 librenderer
*A sort of SDL in your terminal, so to speak. All in a single C99 header file.*

## Getting started
Copy `librenderer.h` into your project

Copypasteable boilerplate if you don't have the time:
```c
#define LIBRENDERER_IMPLEMENTATION
#include "librenderer.h"

int main(void)
{
    librenderer_displaycontext_t d = librenderer_initdisplay(40,40);
    
    // hmm... which pixels do I put on screen...
    librenderer_showdisplay(d);

    librenderer_destroydisplay(&d);
    return 0;
}
```
No prefix variant
```c
#define LIBRENDERER_NOPREFIX
#define LIBRENDERER_IMPLEMENTATION
#include "librenderer.h"

int main(void)
{
    displaycontext_t d = initdisplay(40,40);
    
    // hmm... which pixels do I put on screen...
    showdisplay(d);

    destroydisplay(&d);
    return 0;
}
```

## Usage guide

### Including librenderer
As your average single header library:
   1. Put `librenderer.h` in somewhere your project tree.
   2. Define the `LIBRENDERER_IMPLEMENTATION` macro
   3. Finally, include `librenderer.h` where needed.

Optionally, before including `librenderer.h`, you can define other macros that adjust certain settings of the library.\
Current macro settings:
   * `LIBRENDERER_NOPREFIX`, which strips the LIBRENDERER prefix of off types and functions \
     It allows you to use, for example, `displaycontext_t` instead of `librenderer_displaycontext_t` \
     Quite handy if it's the sole dependency of your project
   * `LIBRENDERER_NOCOLOR` makes librenderer never use true-color escape codes, however this means you will have black and white
   * if using no color, `LIBRENDERER_GRAYSCALE_THRESHOLD` defines at which value (from 0 to 255) a pixel is considered bright.
   * If your terminal does not support UTF-8 characters, define `LIBRENDERER_NO_UTF8`. The frame and the pixels will be displayed in a different way.

### Manipulating displays
A display is basically a librenderer context \
It's even in the type name.

First declare a display like so:
```c
    librenderer_displaycontext_t d = librenderer_initdisplay(WIDTH,HEIGHT);
```
Of course, replace WIDTH and HEIGHT with positive integers

Since displays are dynamically allocated (malloc!!!!!), you should free them.
```c
    librenderer_destroydisplay(&d);
```

This also means you can't easily resize a display (yet), maybe try realloc on `librenderer_displaycontext_t.data`, but this has yet to be tested and implemented

## Optional: compilation
Usually, you won't need to compile librenderer, as it's a single header library. It defeats the entire point.
In case you really need a binary, run this to generate a shared object (for dynamic linking)
```
$ make librenderer.so
```
Or, to generate a static library:
```
$ make librenderer.a
```

You can also compile some demos:
```
$ make examples
```
Then find the demo executables in `examples/`
