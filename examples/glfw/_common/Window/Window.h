#pragma once

#include <string>
#include <GLFW/glfw3.h> 
#include "global.h"

namespace Example
{

class EXAMPLE_EXPORT Window
{
public:
  explicit Window(std::string val = "Traits3D Demo", int majorversion = 4, int minorversion = 0);
  virtual ~Window();
  bool onClose() const;
  void update();

private:
  GLFWwindow* window_;
  bool init(std::string val, int majorversion, int minorversion);
};

} // ns