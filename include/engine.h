#ifndef ENGINE_H
#define ENGINE_H

typedef struct Engine_t
{
    volatile int WindowWidth, WindowHeight;
    int ShaderProgram;
    unsigned int VBO, VAO, EBO;

    int Texture;
} Engine_t;

int Engine_init (Engine_t* engine);
int Engine_render (Engine_t* engine);

#endif
