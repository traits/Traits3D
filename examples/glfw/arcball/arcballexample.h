#pragma once

#include <memory>

#include "glb/shader.h"
#include "glb/vao.h"
#include "glb/vbo.h"

#include "Window/Window.h"
#include "traits3d/arcball.h"

class ExampleArcBall
{

public:
    ExampleArcBall();

    std::shared_ptr<Example::Window> window()
    {
        return window_;
    }

    const float PI2 = 2.0 * 3.1415926535f;              // PI Squared

    bool initializeGL();

    bool loadData();
    void update();                // Perform Motion Updates Here
    void draw();


private:
    std::shared_ptr<Example::Window> window_;
    traits3d::ArcBall    arcBall;                     // ArcBall Instance
    bool        isDragging = false;                   // Dragging The Mouse?
    glm::mat4   Transform;        // Final Transform
    glm::mat3   lastRot;          // Last Rotation
    glm::mat3   thisRot;          // This Rotation
    // User Defined Variables
    void setupSphere(int NumMajor, int NumMinor, float Radius);
    void Torus(float MinorRadius, float MajorRadius);         // Draw A Torus With Normals

    std::unique_ptr<glb::Shader> shader_;
    std::unique_ptr<glb::VAO> vao_;
    std::unique_ptr<glb::VBO> vbo_torus_;
    std::unique_ptr<glb::VBO> vbo_sphere_;
};