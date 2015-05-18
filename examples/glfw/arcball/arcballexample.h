#pragma once

#include <memory>

#include "traits3d/glbase/shader.h"
#include "traits3d/glbase/vao.h"
#include "traits3d/glbase/vbo.h"

#include "Window/Window.h"
#include "traits3d/arcball.h"

class ExampleArcBall
{

public:
  ExampleArcBall();

  std::shared_ptr<Example::Window> window() { return window_; }


  const float PI2 = 2.0*3.1415926535f;                // PI Squared

  bool initializeGL();         

  bool loadData();
  void update();                // Perform Motion Updates Here
  void draw();


  private:
    std::shared_ptr<Example::Window> window_;
    Traits3D::ArcBall    arcBall;                     // ArcBall Instance
    bool        isDragging = false;                   // Dragging The Mouse?
    glm::mat4   Transform;        // NEW: Final Transform
    glm::mat3   LastRot;          // NEW: Last Rotation
    glm::mat3   ThisRot;          // NEW: This Rotation
    // User Defined Variables
    void Sphere(int NumMajor, int NumMinor, float Radius);
    void Torus(float MinorRadius, float MajorRadius);         // Draw A Torus With Normals

    std::unique_ptr<Traits3D::GL::Shader> shader_;
    std::unique_ptr<Traits3D::GL::VAO> vao_;
    std::unique_ptr<Traits3D::GL::VBO> vbo_torus_;
    std::unique_ptr<Traits3D::GL::VBO> vbo_sphere_;
};