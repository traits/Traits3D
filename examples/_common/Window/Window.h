#pragma once

#include <string>
#include <GLFW/glfw3.h> 
#include "global.h"

namespace Example
{

  class EXAMPLE_EXPORT Window
{
public:
  explicit Window(std::string val = "Protean3D Demo");
  virtual ~Window();
  bool onClose() const;
  void update();

private:
  GLFWwindow* window_;
  bool init(std::string val);
};

} // ns