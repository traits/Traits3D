#pragma once

#include <memory>
#include "Window/Window.h"
#include "traits3d/arcball.h"

class ExampleArcBall
{

public:
  ExampleArcBall();

  std::shared_ptr<Example::Window> window() { return window_; }


  const float PI2 = 2.0*3.1415926535f;                // PI Squared

  bool initialize();            // Any GL Init Code & User Initialization Goes Here

  void update();                // Perform Motion Updates Here
  void draw();


  private:
    std::shared_ptr<Example::Window> window_;
    Traits3D::ArcBall    arcBall;                     // NEW: ArcBall Instance
    bool        isDragging = false;                   // NEW: Dragging The Mouse?
    glm::mat4   Transform;        // NEW: Final Transform
    glm::mat3   LastRot;          // NEW: Last Rotation
    glm::mat3   ThisRot;          // NEW: This Rotation
    // User Defined Variables
    void Sphere(int NumMajor, int NumMinor, float Radius);
    void Torus(float MinorRadius, float MajorRadius);         // Draw A Torus With Normals
};