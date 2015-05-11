#include <iostream>
#include "Window.h"


Example::CallBack* Example::CallBack::instance_p = nullptr;

/**********************************************************************
* GLFW callback functions
*********************************************************************/

void Example::CallBack::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (instance_p)
    instance_p->keyCallback(window, key, scancode, action, mods);
}

void Example::CallBack::mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
  if (instance_p)
    instance_p->mouseMoveCallback(window, xpos, ypos);
}

void Example::CallBack::mouse_callback(GLFWwindow* window, int button, int action, int modifiers)
{
  if (instance_p)
    instance_p->mouseCallback(window, button, action, modifiers);
}

void Example::Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  switch (key)
  {
  case GLFW_KEY_ESCAPE:
    /* Exit program on Escape */
    glfwSetWindowShouldClose(window, GL_TRUE);
    break;
  }
}

void Example::Window::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
  if (!left_mouse_button_pressed_)
    return;

  xpos_ = xpos;
  ypos_ = ypos;
  std::cerr << "move: x: " << xpos_ << "  y: " << ypos_ << std::endl;
}

void Example::Window::mouseCallback(GLFWwindow* window, int button, int action, int modifiers)
{
  if (action == GLFW_PRESS)
  {
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
      right_mouse_button_pressed_ = true;
      // ... some code
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      left_mouse_button_pressed_ = true;
      glfwGetCursorPos(window, &xpos_, &ypos_);
      std::cerr << "x: " << xpos_ << "  y: " << ypos_ << std::endl;
    }
  }
  else // GLFW_RELEASE
  {
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
      right_mouse_button_pressed_ = false;
      // ... some code
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
      left_mouse_button_pressed_ = false;
      glfwGetCursorPos(window, &xpos_, &ypos_);
      std::cerr << "x: " << xpos_ << "  y: " << ypos_ << std::endl;
    }
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}


bool Example::Window::init(std::string val, int majorversion, int minorversion)
{
  if (!glfwInit())
  {
    //fprintf(stderr, "ERROR: Unable to initialize GLFW\n");
    return false;
  }

  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorversion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorversion);

  if (majorversion >= 3)
  {
	  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
  }

  window_ = glfwCreateWindow(2*640, 2*480, val.c_str(), NULL, NULL);
  if (!window_)
  {
    //fprintf(stderr, "ERROR: Unable to create the OpenGL context and associated window\n");
    glfwTerminate();
    return false;
  }

  /* Register events callback */
  glfwSetKeyCallback(window_, CallBack::key_callback);
  glfwSetMouseButtonCallback(window_, CallBack::mouse_callback);
  glfwSetCursorPosCallback(window_, CallBack::mouse_move_callback);
  glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
  glfwMakeContextCurrent(window_);

  /* setup the scene ready for rendering */
  glClearColor(0.7f, 0.7f, 0.7f, 0.0f);

  // turn vsync off
  glfwSwapInterval(0);

  return true;
}

Example::Window::Window(std::string val /*= "Traits3D Demo"*/, int majorversion/* = 4*/, int minorversion/* = 0*/)
{
  instance_p = this;
  init(val, majorversion, minorversion);
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
