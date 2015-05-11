#pragma once

#include <string>
#include <GLFW/glfw3.h> 
#include "global.h"

namespace Example
{

  class EXAMPLE_EXPORT CallBack
{
public:
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
  static void mouse_callback(GLFWwindow* window, int button, int action, int modifiers);

  virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
  virtual void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) = 0;
  virtual void mouseCallback(GLFWwindow* window, int button, int action, int modifiers) = 0;

protected:
  static CallBack* instance_p;
};

class EXAMPLE_EXPORT Window : public CallBack
{
public:
  explicit Window(std::string val = "Traits3D Demo", int majorversion = 4, int minorversion = 0);
  virtual ~Window();
  bool onClose() const;
  void update();

  double xPos() const { return xpos_; }
  double yPos() const { return ypos_; }

  bool leftMouseButtonPressed() const { return left_mouse_button_pressed_; }
  bool rightMouseButtonPressed() const { return right_mouse_button_pressed_; }

protected:
  void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
  void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) override;
  void mouseCallback(GLFWwindow* window, int button, int action, int modifiers) override;

private:
  GLFWwindow* window_;
  bool init(std::string val, int majorversion, int minorversion);
  
  bool left_mouse_button_pressed_ = false;
  bool right_mouse_button_pressed_ = false;
  double xpos_ = 0.0;
  double ypos_ = 0.0;
};

} // ns