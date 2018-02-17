#ifndef MAIN_H
#define MAIN_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
EM_BOOL ResizeHandler(int eventType, const EmscriptenUiEvent *uiEvent, void *userData);
EM_BOOL MouseHandler(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);
#endif

#include "graphics.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void window_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);
void loop (void);

#include "engine.h"

extern Engine_t Engine;

#endif
