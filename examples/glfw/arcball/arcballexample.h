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

    std::unique_ptr<traits3d::gl::Shader> shader_;
    std::unique_ptr<traits3d::gl::VAO> vao_;
    std::unique_ptr<traits3d::gl::VBO> vbo_torus_;
    std::unique_ptr<traits3d::gl::VBO> vbo_sphere_;
};