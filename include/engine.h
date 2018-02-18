#ifndef ENGINE_H
#define ENGINE_H

#include "graphics.h"

typedef struct Engine_t
{
    GLFWwindow* Window;
    int ShaderProgram;
    unsigned int VBO, VAO, EBO;
    unsigned int PlaDataVBO, PlaLifeDataVBO;
    int     TileTexture;
    float   TileZoom;
} Engine_t;

int Engine_init (Engine_t* engine);
int Engine_render (Engine_t* engine);

#endif
