#include <stdio.h>
#include "main.h"
#include "shader.h"
#include "engine.h"
#include "texture.h"

#define ENGINE_ATTRIB_POSITION  0
#define ENGINE_ATTRIB_COLOR     1
#define ENGINE_ATTRIB_TEXCOORD  2

int Engine_init (Engine_t* engine)
{
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

    // position attribute
    glVertexAttribPointer(ENGINE_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(ENGINE_ATTRIB_POSITION);

    engine->Texture = loadTexture("textures/tileset.png");

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    engine->TileSize = 30.0;

    return 0;
}



int Engine_render (Engine_t* engine)
{
    glUseProgram(engine->ShaderProgram);

    int width, height;
    glfwGetWindowSize(engine->Window, &width, &height);
    glUniform2f(glGetUniformLocation(engine->ShaderProgram, "WindowSize"), width, height);

    glUniform1f(glGetUniformLocation(engine->ShaderProgram, "TileSize"), engine->TileSize);

    // bind Texture
    glBindTexture(GL_TEXTURE_2D, engine->Texture);

    glBindVertexArray(engine->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, ENGINE_ATTRIB_POSITION, (width/engine->TileSize + 1) * (height/engine->TileSize + 1) );
    // glBindVertexArray(0); // no need to unbind it every time
    return 0;
}
