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

EXAMPLES = examples/test examples/randpix examples/randline examples/bball examples/quadratic_graph
# EXAMPLES = examples/test examples/randpix examples/randline examples/bball examples/quadratic_graph examples/snake examples/raycast examples/pong

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

# --- Cleanup code ---

clean:
	@rm -rvf $(EXAMPLES) librenderer.o librenderer.so librenderer.a

.PHONY: clean
