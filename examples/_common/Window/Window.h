#pragma once

#include <GLFW/glfw3.h> 
#include "global.h"

namespace Example
{

  class EXAMPLE_EXPORT Window
{
public:
  Window();
  virtual ~Window();
  GLFWwindow* window;

private:
  bool init();
};

} // ns