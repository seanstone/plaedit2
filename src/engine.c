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

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    float quadVertices[] =
    {
        // positions     // colors
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &engine->VAO);
    glGenBuffers(1, &engine->VBO);
    glGenBuffers(1, &engine->EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(engine->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, engine->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, engine->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(ENGINE_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(ENGINE_ATTRIB_POSITION);
    // color attribute
    glVertexAttribPointer(ENGINE_ATTRIB_COLOR, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(ENGINE_ATTRIB_COLOR);
    // texture coord attribute
    glVertexAttribPointer(ENGINE_ATTRIB_TEXCOORD, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(ENGINE_ATTRIB_TEXCOORD);

    engine->Texture = loadTexture("textures/container.jpg");

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    return 0;
}

int Engine_render (Engine_t* engine)
{
    glUseProgram(engine->ShaderProgram);

    int width, height;
    glfwGetWindowSize(engine->Window, &width, &height);
    glUniform2f(glGetUniformLocation(engine->ShaderProgram, "WindowSize"), width, height);

    // bind Texture
    glBindTexture(GL_TEXTURE_2D, engine->Texture);

    glBindVertexArray(engine->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, ENGINE_ATTRIB_POSITION, 2);
    // glBindVertexArray(0); // no need to unbind it every time
    return 0;
}
