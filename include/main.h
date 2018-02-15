#ifndef MAIN_H
#define MAIN_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
EM_BOOL ResizeHandler(int eventType, const EmscriptenUiEvent *uiEvent, void *userData);
EM_BOOL MouseHandler(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);
#endif

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#ifndef __EMSCRIPTEN__
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void loop (void);

#endif
