#ifndef SHADER_H
#define SHADER_H

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#ifndef __EMSCRIPTEN__
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

int loadShader (char* path, GLenum shaderType); /* GL_VERTEX_SHADER or GL_FRAGMENT_SHADER etc. */
int linkProgram (int vertexShader, int fragmentShader);
int loadProgram (char* vertexShaderPath, char* fragmentShaderPath);

#endif
