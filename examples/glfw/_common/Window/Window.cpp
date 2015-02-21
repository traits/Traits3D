#include <iostream>
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

static void mouse_callback(GLFWwindow* window, int button, int action, int modifiers)
{
  if (action == GLFW_PRESS)
  {
	  if (button == GLFW_MOUSE_BUTTON_RIGHT)
	  {
	    // ... some code
	  }
	  else if (button == GLFW_MOUSE_BUTTON_LEFT)
	  {
      double x, y;
      glfwGetCursorPos(window, &x, &y);
      std::cerr << "x: " << x << "  y: " << y << std::endl;
	  }
  }
  //else // GLFW_RELEASE
  //{
  //
  //}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}


bool Example::Window::init(std::string val)
{
  if (!glfwInit())
  {
    //fprintf(stderr, "ERROR: Unable to initialize GLFW\n");
    return false;
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

  window_ = glfwCreateWindow(1024, 768, val.c_str(), NULL, NULL);
  if (!window_)
  {
    //fprintf(stderr, "ERROR: Unable to create the OpenGL context and associated window\n");
    glfwTerminate();
    return false;
  }

  /* Register events callback */
  glfwSetKeyCallback(window_, key_callback);
  glfwSetMouseButtonCallback(window_, mouse_callback);
  glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
  glfwMakeContextCurrent(window_);

  /* setup the scene ready for rendering */
  glClearColor(0.7f, 0.7f, 0.7f, 0.0f);

  // turn vsync off
  glfwSwapInterval(0);

  return true;
}

Example::Window::Window(std::string val /*= "Traits3D Demo"*/)
{
  init(val);
}

Example::Window::~Window()
{
  glfwDestroyWindow(window_);
  glfwTerminate();
}

bool Example::Window::onClose() const
{
  return 0 != glfwWindowShouldClose(window_);
}

void Example::Window::update()
{
  /* display and process events through callbacks */
  glfwSwapBuffers(window_);
  glfwPollEvents();
}
