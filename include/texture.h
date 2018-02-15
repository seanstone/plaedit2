#ifndef TEXTURE_H
#define TEXTURE_H

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#ifndef __EMSCRIPTEN__
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

int loadTexture (char* path);

#endif
