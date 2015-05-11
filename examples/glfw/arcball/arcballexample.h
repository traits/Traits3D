#pragma once

#include <memory>
#include "Window/Window.h"
#include "arcball.h"

class ExampleArcBall
{

public:
  ExampleArcBall();

  std::shared_ptr<Example::Window> window() { return window_; }


  const float PI2 = 2.0*3.1415926535f;								// PI Squared

  bool Initialize();						// Any GL Init Code & User Initialiazation Goes Here

  void Deinitialize();											// Any User DeInitialization Goes Here

  void Update();									// Perform Motion Updates Here
  void Draw();


  private:
    std::shared_ptr<Example::Window> window_;
    Point2fT    MousePt;												// NEW: Current Mouse Point
    ArcBall    arcBall; 		                // NEW: ArcBall Instance
    bool        isDragging = false;					                    // NEW: Dragging The Mouse?
    Matrix4fT   Transform;				// NEW: Final Transform
    Matrix3fT   LastRot;					// NEW: Last Rotation
    Matrix3fT   ThisRot;					// NEW: This Rotation
    // User Defined Variables
    GLUquadricObj *quadratic;											// Used For Our Quadric

    void Torus(float MinorRadius, float MajorRadius);					// Draw A Torus With Normals
};