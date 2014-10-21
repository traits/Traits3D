#include "Window.h"

/**********************************************************************
* GLFW callback functions
*********************************************************************/

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  switch (key)
  {
  case GLFW_KEY_ESCAPE:
    /* Exit program on Escape */
    glfwSetWindowShouldClose(window, GL_TRUE);
    break;
  }
}

bool Example::Window::init()
{
  if (!glfwInit())
  {
    //fprintf(stderr, "ERROR: Unable to initialize GLFW\n");
    return false;
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

  window = glfwCreateWindow(1024, 768, "GLFW OpenGL3 Heightmap demo", NULL, NULL);
  if (!window)
  {
    //fprintf(stderr, "ERROR: Unable to create the OpenGL context and associated window\n");
    glfwTerminate();
    return false;
  }

  /* Register events callback */
  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);

  return true;
}

Example::Window::Window()
{
  init();
}

Example::Window::~Window()
{
  glfwTerminate();
}
