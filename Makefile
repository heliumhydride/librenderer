include config.mk

all:
	@cat make.msg

# --- Binary versoin of the library ---

librenderer.o: librenderer.h
	$(CC) -x c $(CFLAGS) -fPIC -c librenderer.h -o librenderer.o

librenderer.so: librenderer.o
	$(CC) -shared $(CFLAGS) librenderer.o -o librenderer.so

librenderer.a: librenderer.o
	$(AR) rcs librenderer.a librenderer.o

# --- Examples & related ---

EXAMPLES = examples/test examples/randpix examples/randline examples/bball examples/quadratic_graph examples/pong examples/resize examples/rect examples/snake examples/raycast

examples: $(EXAMPLES)

examples/test: examples/test.c librenderer.h
	$(CC) $(CFLAGS) $< -o $@

examples/randpix: examples/randpix.c librenderer.h
	$(CC) $(CFLAGS) $< -o $@

examples/randline: examples/randline.c librenderer.h
	$(CC) $(CFLAGS) $< -o $@

examples/bball: examples/bball.c librenderer.h
	$(CC) $(CFLAGS) $< -o $@

examples/quadratic_graph: examples/quadratic_graph.c librenderer.h
	$(CC) $(CFLAGS) $< -o $@

examples/pong: examples/pong.c librenderer.h
	$(CC) $(CFLAGS) $< -o $@

examples/resize: examples/resize.c librenderer.h
	$(CC) $(CFLAGS) $< -o $@

examples/rect: examples/rect.c librenderer.h
	$(CC) $(CFLAGS) $< -o $@

# --- Cleanup code ---

clean:
	@rm -rvf $(EXAMPLES) librenderer.o librenderer.so librenderer.a

.PHONY: clean
