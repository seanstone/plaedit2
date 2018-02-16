#ifndef SHADER_H
#define SHADER_H

#include "graphics.h"

int loadShader (char* path, GLenum shaderType); /* GL_VERTEX_SHADER or GL_FRAGMENT_SHADER etc. */
int linkProgram (int vertexShader, int fragmentShader);
int loadProgram (char* vertexShaderPath, char* fragmentShaderPath);

#endif
