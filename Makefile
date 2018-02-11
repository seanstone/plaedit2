# Binaryen required to compile to WASM
export BINARYEN := /usr
EMFLAGS += -s WASM=1

INCLUDE += -I glad/include
CFLAGS += -s WASM=1
LDFLAGS += -lglfw3 -lGL -lpthread -lm -ldl
XLDFLAGS += -lX11 -lXrandr -lXi -lXcursor -lXxf86vm -lXinerama
EMFLAGS += -s NO_EXIT_RUNTIME=1 -s USE_GLFW=3

.PHONY: x
x:
	mkdir -p build/
	$(CC) $(CFLAGS) $(INCLUDE) src/main.c glad/src/glad.c $(LDFLAGS) $(XLDFLAGS) -o build/main

.PHONY: em
em:
	mkdir -p dist/
	emcc $(EMFLAGS) $(CFLAGS) $(INCLUDE) src/main.c $(LDFLAGS) -o dist/main.js

.PHONY: clean
clean:
	rm -rf dist/ build/
