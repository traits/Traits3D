#include <glm\gtc\matrix_transform.hpp>
#include "glb/transformation.h"
#include "glb/shader_std.h"
#include "traits3d/types.h"
#include "arcballexample.h"

using namespace traits3d;

ExampleArcBall::ExampleArcBall()
{
    Transform = glm::mat4(1);
    lastRot = glm::mat3(1);
    thisRot = glm::mat3(1);
    window_ = std::make_shared<Example::Window>("GLFW OpenGL3 Arcball Demo");
    arcBall.setBounds(1280.0f, 960.0f);
}

bool ExampleArcBall::initializeGL() // Any GL Init Code
{
    arcBall.setBounds((GLfloat)1280, (GLfloat)960);  // Update mouse bounds for arcball
    // Start Of User Initialization
    glClearColor(0.8f, 0.8f, 0.8f, 0.5f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_FLAT);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// Set Perspective Calculations To Most Accurate
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);
    shader_ = std::make_unique<glb::Shader>();

    if (!shader_->create(glb::shadercode::Vertex::Line, glb::shadercode::Fragment::Simple))
        return false;

    vao_ = std::make_unique<glb::VAO>();
    vbo_torus_ = std::make_unique<glb::VBO>(vao_.get(), 3);
    vbo_sphere_ = std::make_unique<glb::VBO>(vao_.get(), 3);
    return true;
}

bool ExampleArcBall::loadData()
{
    Torus(0.30f, 1.00f);
    setupSphere(20, 20, 1.3f);
    return true;
}

void ExampleArcBall::update() // Perform Motion Updates Here
{
    glm::vec2 pos;
    pos.x = static_cast<float>(window_->xPos());
    pos.y = static_cast<float>(window_->yPos());

    if (window_->rightMouseButtonPressed()) // If Right Mouse Clicked, Reset All Rotations
    {
        lastRot = glm::mat3(1);               // Reset Rotation
        thisRot = glm::mat3(1);               // Reset Rotation
        ArcBall::setRotationalComponent(Transform, thisRot);    // Reset Rotation
    }

    if (!isDragging)
    {
        if (window_->leftMouseButtonPressed())  // First Click
        {
            isDragging = true;                    // Prepare For Dragging
            lastRot = thisRot;                    // Set Last Static Rotation To Last Dynamic One
            arcBall.start(pos);                   // Update Start Vector And Prepare For Dragging
        }
    }
    else
    {
        if (window_->leftMouseButtonPressed())                // Still Clicked, So Still Dragging
        {
            glm::quat quat = arcBall.quaternion(pos);           // Update End Vector And Get Rotation As Quaternion
            thisRot = ArcBall::rotationMatrix(quat);  // Convert Quaternion Into Matrix3fT
            thisRot *= lastRot;                                 // Accumulate Last Rotation Into This One
            ArcBall::setRotationalComponent(Transform, thisRot);  // Set Our Final Transform's Rotation From This One
        }
        else                            // No Longer Dragging
            isDragging = false;
    }
}

void ExampleArcBall::setupSphere(int NumMajor, int NumMinor, float radius)
{
    float majorStep, minorStep;
    float a, b, c, r0, r1;
    float x, y, z0, z1;
    majorStep = PI2 / 2 / NumMajor;
    minorStep = PI2 / NumMinor;
    std::vector<TripleF> pos(2 * (NumMinor + 1) * (NumMajor + 1));
    int curr = 0;

    for (int i = 0; i <= NumMajor; ++i)
    {
        a = i * majorStep;
        b = a + majorStep;
        r0 = radius * std::sin(a);
        r1 = radius * std::sin(b);
        z0 = radius * std::cos(a);
        z1 = radius * std::cos(b);

        for (int j = 0; j <= NumMinor; ++j)
        {
            c = j * minorStep;
            x = std::cos(c);
            y = std::sin(c);
            //glNormal3f((x * r0) / radius, (y * r0) / radius, z0 / radius);
            //glVertex3f(x * r0, y * r0, z0);
            pos[curr++] = TripleF(x * r0, y * r0, z0);
            //glNormal3f((x * r1) / radius, (y * r1) / radius, z1 / radius);
            //glVertex3f(x * r1, y * r1, z1);
            pos[curr++] = TripleF(x * r1, y * r1, z1);
        }
    }

    vbo_sphere_->setData(pos);
}

void ExampleArcBall::Torus(float MinorRadius, float MajorRadius) // Draw A Torus With Normals
{
    const int size = 30;
    std::vector<TripleF> pos(2 * size * (size + 1));
    int curr = 0;

    for (int i = 0; i < size; ++i)                    // Stacks
    {
        for (int j = -1; j < size; ++j)                 // Slices
        {
            float wrapFrac = (j % size) / (float)size;
            float phi = PI2 * wrapFrac;
            float sinphi = float(sin(phi));
            float cosphi = float(cos(phi));
            float r = MajorRadius + MinorRadius * cosphi;
            //glNormal3f(float(sin(PI2*(i % size + wrapFrac) / (float)size))*cosphi, sinphi, float(cos(PI2*(i % size + wrapFrac) / (float)size))*cosphi);
            //glVertex3f(float(sin(PI2*(i % size + wrapFrac) / (float)size))*r, MinorRadius*sinphi, float(cos(PI2*(i % size + wrapFrac) / (float)size))*r);
            pos[curr++] = TripleF(float(sin(PI2 * (i % size + wrapFrac) / (float)size)) * r, MinorRadius * sinphi, float(cos(PI2 * (i % size + wrapFrac) / (float)size)) * r);
            //glNormal3f(float(sin(PI2*(i + 1 % size + wrapFrac) / (float)size))*cosphi, sinphi, float(cos(PI2*(i + 1 % size + wrapFrac) / (float)size))*cosphi);
            //glVertex3f(float(sin(PI2*(i + 1 % size + wrapFrac) / (float)size))*r, MinorRadius*sinphi, float(cos(PI2*(i + 1 % size + wrapFrac) / (float)size))*r);
            pos[curr++] = TripleF(float(sin(PI2 * (i + 1 % size + wrapFrac) / (float)size)) * r, MinorRadius * sinphi, float(cos(PI2 * (i + 1 % size + wrapFrac) / (float)size)) * r);
        }
    }

    vbo_torus_->setData(pos);
}

void ExampleArcBall::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       // Clear Screen And Depth Buffer
    glm::mat4 proj = glm::perspectiveFov(45.0f, 1280.0f, 960.0f, 1.0f, 100.0f);
    shader_->setUniformMatrix(proj, glb::shadercode::Var::proj_matrix);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glm::mat4 mv = glm::mat4(1);
    mv = glm::translate(mv, glm::vec3(-1.5f, 0.0f, -6.0f));
    mv = mv * Transform;
    shader_->setUniformMatrix(mv, glb::shadercode::Var::mv_matrix);
    vbo_torus_->bindAttribute(shader_->programId(), glb::shadercode::Var::v_coordinates);
    shader_->setUniformVec4(glm::vec4(0.35f, 0.35f, 1.0f, 1.0f), glb::shadercode::Var::v_in_color);
    vbo_torus_->draw(GL_TRIANGLE_STRIP);
    mv = glm::mat4(1);
    mv = glm::translate(mv, glm::vec3(1.5f, 0.0f, -6.0f));
    mv = mv * Transform;
    shader_->setUniformMatrix(mv, glb::shadercode::Var::mv_matrix);
    vbo_sphere_->bindAttribute(shader_->programId(), glb::shadercode::Var::v_coordinates);
    shader_->setUniformVec4(glm::vec4(1.0f, 0.35f, 0.35f, 1.0f), glb::shadercode::Var::v_in_color);
    vbo_sphere_->draw(GL_TRIANGLE_STRIP);
}
