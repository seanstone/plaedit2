#include <stdio.h>
#include "main.h"
#include "shader.h"
#include "engine.h"
#include "texture.h"

#define ENGINE_ATTRIB_POSITION  0
#define ENGINE_ATTRIB_INSTANCE  1

int Engine_init (Engine_t* engine)
{
    /* Shader program */
    engine->ShaderProgram = loadProgram("glsl/vertex.glsl", "glsl/fragment.glsl");

    /* VAO */
    glGenVertexArrays(1, &engine->VAO);
    glBindVertexArray(engine->VAO);

    /* Quad vertices */
    glGenBuffers(1, &engine->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, engine->VBO);
    float quad[] = {
        // positions
        1.0f, 1.0f,   // top right
        1.0f, 0.0f,   // bottom right
        0.0f, 0.0f,   // bottom left
        0.0f, 1.0f    // top left
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

    /* Quad elements */
    glGenBuffers(1, &engine->EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, engine->EBO);
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* Quad attribute */
    glVertexAttribPointer(ENGINE_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(ENGINE_ATTRIB_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind

    /* Instance VBO */
    glGenBuffers(1, &engine->instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, engine->instanceVBO);
    /* Instance attribute */
    glVertexAttribPointer(ENGINE_ATTRIB_INSTANCE, 2, GL_UNSIGNED_BYTE, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(ENGINE_ATTRIB_INSTANCE);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(ENGINE_ATTRIB_INSTANCE, 1); // tell OpenGL this is an instanced vertex attribute.

    /* Tileset texture */
    engine->TileTexture = loadTexture("textures/tileset.png");

    /* Unbind */
    //glBindVertexArray(0);

    /* Default options */
    engine->TileZoom = 30.0;

    return 0;
}

int Engine_render (Engine_t* engine)
{
    glUseProgram(engine->ShaderProgram);

    /* Set uniforms */
    int width, height;
    glfwGetWindowSize(engine->Window, &width, &height);
    glUniform2i(glGetUniformLocation(engine->ShaderProgram, "WindowSize"), width, height);
    glUniform2i(glGetUniformLocation(engine->ShaderProgram, "TextureSize"), 1200, 720);
    glUniform1f(glGetUniformLocation(engine->ShaderProgram, "TileZoom"), engine->TileZoom);

    glBindTexture(GL_TEXTURE_2D, engine->TileTexture);

    glBindVertexArray(engine->VAO);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, ENGINE_ATTRIB_POSITION, 128 * 64);
    //glBindVertexArray(0);

    return 0;
}
