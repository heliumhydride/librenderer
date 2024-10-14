include config.mk

all: shared static

# --- librenderer library ---
shared: librenderer.so.1
static: librenderer.a

librenderer.o: librenderer.c
	$(CC) -fPIC -lm $(CFLAGS) -o librenderer.o -c librenderer.c

librenderer.so.1: librenderer.o
	$(CC) -lm -shared $(CFLAGS) -o librenderer.so.1 librenderer.o

librenderer.a: librenderer.o
	$(AR) rcs librenderer.a librenderer.o

# --- Examples & related ---
util.o: util.c
	$(CC) -c -lsodium $(CFLAGS) -o util.o util.c

examples: o/bball o/randpix o/randline o/cosgraph

examples/bball.o: examples/bball.c
	$(CC) -c -lsodium $(CFLAGS) -o examples/bball.o examples/bball.c

o/bball: examples/bball.o util.o librenderer.a
	$(CC) -lsodium $(CFLAGS) -o o/bball examples/bball.o util.o librenderer.a

examples/randpix.o: examples/randpix.c
	$(CC) -c -lsodium $(CFLAGS) -o examples/randpix.o examples/randpix.c

o/randpix: examples/randpix.o util.o librenderer.a
	$(CC) -lsodium $(CFLAGS) -o o/randpix examples/randpix.o util.o librenderer.a

examples/randline.o: examples/randline.c
	$(CC) -c -lsodium $(CFLAGS) -o examples/randline.o examples/randline.c

o/randline: examples/randline.o util.o librenderer.a
	$(CC) -lsodium $(CFLAGS) -o o/randline examples/randline.o util.o librenderer.a

examples/cosgraph.o: examples/cosgraph.c
	$(CC) -c $(CFLAGS) -o examples/cosgraph.o examples/cosgraph.c

o/cosgraph: examples/cosgraph.o librenderer.a
	$(CC) $(CFLAGS) -o o/cosgraph examples/cosgraph.o librenderer.a -lm

clean:
	rm -rf *.o examples/*.o *.so* *.a o/*

.PHONY: clean examples shared static
