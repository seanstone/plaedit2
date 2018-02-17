#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "engine.h"

Engine_t Engine;

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(Engine.Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(Engine.Window, true);
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

    int width, height;
    #ifdef __EMSCRIPTEN__
    double width_d, height_d;
    emscripten_get_element_css_size("#canvas", &width_d, &height_d);
    width = (int) width_d; height = (int) height_d;
    #else
    width = 800; height = 600;
    #endif

    Engine.Window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    if (Engine.Window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    printf("GLFW window created: %u, %u\n", width, height);
    glfwMakeContextCurrent(Engine.Window);
    glViewport(0, 0, width, height);

    #ifndef __EMSCRIPTEN__
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }
    #endif

    Engine_init(&Engine);

    #ifdef __EMSCRIPTEN__
    emscripten_set_resize_callback(0, 0, true, ResizeHandler);
    emscripten_set_mousedown_callback(0, 0, true, MouseHandler);
    emscripten_set_mouseup_callback(0, 0, true, MouseHandler);
    emscripten_set_mousemove_callback(0, 0, true, MouseHandler);
    #endif
    glfwSetFramebufferSizeCallback(Engine.Window, framebuffer_size_callback);
    glfwSetWindowSizeCallback(Engine.Window, window_size_callback);
    glfwSetScrollCallback(Engine.Window, scroll_callback);

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
    #else
    while(!glfwWindowShouldClose(Engine.Window))
    {
        loop();
    }
    glfwTerminate();
    #endif

    return 0;
}

void loop (void)
{
    processInput(Engine.Window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Engine_render(&Engine);

    glfwSwapBuffers(Engine.Window);
    glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //printf("framebuffer_size_callback: %u, %u\n", width, height);
    //glViewport(0, 0, width, height);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    //printf("window_size_callback: %u, %u\n", width, height);
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //printf("scroll_callback: %f, %f\n", xoffset, yoffset);
    if (yoffset > 0 && Engine.TileSize > 1.0) Engine.TileSize /= 1.1;
    else if (yoffset < 0) Engine.TileSize *= 1.1;
    printf("Engine.TileSize: %f\n", Engine.TileSize);
}

#ifdef __EMSCRIPTEN__
EM_BOOL ResizeHandler(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
    //printf("ResizeHandler: %u, %u\n", uiEvent->documentBodyClientWidth, uiEvent->documentBodyClientHeight);
    emscripten_set_canvas_element_size("#canvas", uiEvent->documentBodyClientWidth, uiEvent->documentBodyClientHeight);
    glfwSetWindowSize(Engine.Window, uiEvent->documentBodyClientWidth, uiEvent->documentBodyClientHeight);
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
