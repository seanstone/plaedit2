#include <stdio.h>
#include <stdbool.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
EM_BOOL ResizeHandler(int eventType, const EmscriptenUiEvent *uiEvent, void *userData);
EM_BOOL MouseHandler(int eventType, const EmscriptenMouseEvent *mouseEvent, void *userData);
#else
#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void loop (void);
GLFWwindow* window;

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main (void)
{
    printf("Hello world!\n");

    #ifdef __EMSCRIPTEN__
    EM_ASM(
		Module.canvas = (function() {
          return document.getElementById('canvas');
	  })();
	);
    #endif

    printf("Initializing GLFW...\n");

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    printf("Creating GLFW window...\n");

    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    printf("GLFW window created\n");

    #ifndef __EMSCRIPTEN__
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }
    #endif

    glViewport(0, 0, 800, 600);

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

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

#ifdef __EMSCRIPTEN__
EM_BOOL ResizeHandler(int eventType, const EmscriptenUiEvent *uiEvent, void *userData)
{
	//emscripten_get_canvas_size(&width, &height, &isFullscreen);
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
