#include "shader.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int loadShader (char* path, GLenum shaderType) /* GL_VERTEX_SHADER or GL_FRAGMENT_SHADER etc. */
{
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        printf("Failed to open shader file: %s\n", path);
        return -1;
    }
    int len[1];
    len[0] = lseek(fd, 0, SEEK_END);
    const char* shaderSource = mmap(0, len[0], PROT_READ, MAP_PRIVATE, fd, 0);

    int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, (const int*)&len);
    glCompileShader(shader);

    // check for shader compile errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Failed to compile shader: %s\n%s\n", path, infoLog);
        return -1;
    }

    close(fd);

    return shader;
}

int linkProgram (int vertexShader, int fragmentShader)
{
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check for linking errors
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Failed to link program\n%s\n", infoLog);
        return -1;
    }
    return shaderProgram;
}

int loadProgram (char* vertexShaderPath, char* fragmentShaderPath)
{
    int vertexShader    = loadShader(vertexShaderPath, GL_VERTEX_SHADER);
    int fragmentShader  = loadShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    int shaderProgram = linkProgram(vertexShader, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}
