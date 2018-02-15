#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "demo.h"

GLFWwindow* window;

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main (void)
{
    printf("Main function begin\n");

    #ifdef __EMSCRIPTEN__
    EM_ASM(
		Module.canvas = (function() {
          return document.getElementById('canvas');
	  })();
	);
    #endif

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    printf("GLFW intialized\n");

    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    printf("GLFW window created\n");
    glfwMakeContextCurrent(window);

    #ifndef __EMSCRIPTEN__
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }
    #endif

    glViewport(0, 0, 800, 600);

    demo_init();

    #ifdef __EMSCRIPTEN__
    emscripten_set_resize_callback(0, 0, true, ResizeHandler);
    emscripten_set_mousedown_callback(0, 0, true, MouseHandler);
    emscripten_set_mouseup_callback(0, 0, true, MouseHandler);
    emscripten_set_mousemove_callback(0, 0, true, MouseHandler);
    #endif
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
    #else
    while(!glfwWindowShouldClose(window))
    {
        loop();
    }
    glfwTerminate();
    #endif

    return 0;
}

void loop (void)
{
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // no need to unbind it every time

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    printf("framebuffer_size_callback:\n");
    glViewport(0, 0, width, height);
}

#ifdef __EMSCRIPTEN__
EM_BOOL ResizeHandler(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
    int width, height, isFullscreen;

    EMSCRIPTEN_RESULT r = emscripten_get_canvas_element_size("#canvas", &width, &height);
    if (r != EMSCRIPTEN_RESULT_SUCCESS)
        ;/* handle error */
    EmscriptenFullscreenChangeEvent e;
    r = emscripten_get_fullscreen_status(&e);
    if (r != EMSCRIPTEN_RESULT_SUCCESS)
        ;/* handle error */
    isFullscreen = e.isFullscreen;

    printf("ResizeHandler: %u %u %u\n", width, height, isFullscreen);

	return true;
}

EM_BOOL MouseHandler(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData)
{
	// int x, y;
	// switch (eventType)
	// {
	// 	case EMSCRIPTEN_EVENT_MOUSEMOVE:
	// 	{
	// 		emscripten_get_canvas_size(&width, &height, &isFullscreen);
	// 		glViewport(0, 0, width, height);
    //
	// 		x = mouseEvent->clientX; y = height - mouseEvent->clientY;
	// 		EM_ASM_( {document.getElementById("mousepos").innerHTML = $0 + ", " + $1; }, x, y);
	// 	}
	// 		break;
	// 	case EMSCRIPTEN_EVENT_MOUSEDOWN:
	// 		break;
	// 	case EMSCRIPTEN_EVENT_MOUSEUP:
	// 		break;
	// 	default:
	// 		break;
	// }
	return true;
}
#endif
