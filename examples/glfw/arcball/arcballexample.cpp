#include <glm\gtc\matrix_transform.hpp>
#include "arcballexample.h"

ExampleArcBall::ExampleArcBall()
{
  Transform = glm::mat4(1);
  LastRot = glm::mat3(1);
  ThisRot = glm::mat3(1);

  window_ = std::make_shared<Example::Window>("GLFW OpenGL3 Arcball Demo", 1, 2);
  arcBall.setBounds(1280.0f, 960.0f);
}

bool ExampleArcBall::initialize() // Any GL Init Code & User Initialiazation Goes Here
{
  glViewport(0, 0, (GLsizei)(1280), (GLsizei)(960));				// Reset The Current Viewport
  glMatrixMode(GL_PROJECTION);										// Select The Projection Matrix
  glLoadIdentity();													// Reset The Projection Matrix
  
  glm::mat4 proj_mat = glm::perspectiveFov(45.0f, 1280.0f, 960.0f,	1.0f, 100.0f);
  glMultMatrixf(&proj_mat[0][0]);
  glMatrixMode(GL_MODELVIEW);										// Select The Modelview Matrix
  glLoadIdentity();													// Reset The Modelview Matrix

  arcBall.setBounds((GLfloat)1280, (GLfloat)960);                 //*NEW* Update mouse bounds for arcball


  // Start Of User Initialization

  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);							// Black Background
  glClearDepth(1.0f);											// Depth Buffer Setup
  glDepthFunc(GL_LEQUAL);										// The Type Of Depth Testing (Less Or Equal)
  glEnable(GL_DEPTH_TEST);										// Enable Depth Testing
  glShadeModel(GL_FLAT);											// Select Flat Shading (Nice Definition Of Objects)
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);				// Set Perspective Calculations To Most Accurate

  glEnable(GL_LIGHT0);											// Enable Default Light
  glEnable(GL_LIGHTING);											// Enable Lighting

  glEnable(GL_COLOR_MATERIAL);									// Enable Color Material

  return true;													// Return TRUE (Initialization Successful)
}

void ExampleArcBall::update() // Perform Motion Updates Here
{
  MousePt.x = static_cast<float>(window_->xPos());
  MousePt.y = static_cast<float>(window_->yPos());

  if (window_->rightMouseButtonPressed())													// If Right Mouse Clicked, Reset All Rotations
  {
    LastRot = glm::mat3(1);								// Reset Rotation
    ThisRot = glm::mat3(1);								// Reset Rotation
    arcBall.setRotationalComponent(Transform, ThisRot);		// Reset Rotation
  }

  if (!isDragging)												// Not Dragging
  {
    if (window_->leftMouseButtonPressed())												// First Click
    {
      isDragging = true;										// Prepare For Dragging
      LastRot = ThisRot;										// Set Last Static Rotation To Last Dynamic One
      arcBall.click(MousePt);								// Update Start Vector And Prepare For Dragging
    }
  }
  else
  {
    if (window_->leftMouseButtonPressed())												// Still Clicked, So Still Dragging
    {
      glm::quat quat = arcBall.drag(MousePt);						// Update End Vector And Get Rotation As Quaternion
      ThisRot = arcBall.rotationMatrix(quat);		// Convert Quaternion Into Matrix3fT

      ThisRot *= LastRot;  // Accumulate Last Rotation Into This One
      arcBall.setRotationalComponent(Transform, ThisRot);	// Set Our Final Transform's Rotation From This One
    }
    else														// No Longer Dragging
      isDragging = false;
  }
}

void ExampleArcBall::Sphere(int NumMajor, int NumMinor, float radius)
{
  float MajorStep, MinorStep;
  float a, b, c, r0, r1;
  float x, y, z0, z1;

  MajorStep = PI2 / 2 / NumMajor;
  MinorStep = PI2 / NumMinor;

  for (int i = 0; i <= NumMajor; ++i)
  {
    a = i * MajorStep;
    b = a + MajorStep;
    r0 = radius * std::sin(a);
    r1 = radius * std::sin(b);
    z0 = radius * std::cos(a);
    z1 = radius * std::cos(b);

    glBegin(GL_TRIANGLE_STRIP);
    for (int j = 0; j <= NumMinor; ++j)
    {
      c = j * MinorStep;
      x = std::cos(c);
      y = std::sin(c);

      glNormal3f((x * r0) / radius, (y * r0) / radius, z0 / radius);
      glVertex3f(x * r0, y * r0, z0);

      glNormal3f((x * r1) / radius, (y * r1) / radius, z1 / radius);
      glVertex3f(x * r1, y * r1, z1);
    }
    glEnd();
  }
}

void ExampleArcBall::Torus(float MinorRadius, float MajorRadius) // Draw A Torus With Normals
{
  int i, j;
  glBegin(GL_TRIANGLE_STRIP);									// Start A Triangle Strip
  for (i = 0; i < 20; i++)										// Stacks
  {
    for (j = -1; j < 20; j++)									// Slices
    {
      float wrapFrac = (j % 20) / (float)20;
      float phi = PI2*wrapFrac;
      float sinphi = float(sin(phi));
      float cosphi = float(cos(phi));

      float r = MajorRadius + MinorRadius*cosphi;

      glNormal3f(float(sin(PI2*(i % 20 + wrapFrac) / (float)20))*cosphi, sinphi, float(cos(PI2*(i % 20 + wrapFrac) / (float)20))*cosphi);
      glVertex3f(float(sin(PI2*(i % 20 + wrapFrac) / (float)20))*r, MinorRadius*sinphi, float(cos(PI2*(i % 20 + wrapFrac) / (float)20))*r);

      glNormal3f(float(sin(PI2*(i + 1 % 20 + wrapFrac) / (float)20))*cosphi, sinphi, float(cos(PI2*(i + 1 % 20 + wrapFrac) / (float)20))*cosphi);
      glVertex3f(float(sin(PI2*(i + 1 % 20 + wrapFrac) / (float)20))*r, MinorRadius*sinphi, float(cos(PI2*(i + 1 % 20 + wrapFrac) / (float)20))*r);
    }
  }
  glEnd();														// Done Torus
}

void ExampleArcBall::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear Screen And Depth Buffer
  glLoadIdentity();												// Reset The Current Modelview Matrix
  glTranslatef(-1.5f, 0.0f, -6.0f);			  // Move Left 1.5 Units And Into The Screen 6.0

  glPushMatrix();													// NEW: Prepare Dynamic Transform
  glMultMatrixf(&Transform[0][0]);				// NEW: Apply Dynamic Transform
  glColor3f(0.75f, 0.75f, 1.0f);
  Torus(0.30f, 1.00f);
  glPopMatrix();													// NEW: Unapply Dynamic Transform

  glLoadIdentity();												// Reset The Current Modelview Matrix
  glTranslatef(1.5f, 0.0f, -6.0f);				// Move Right 1.5 Units And Into The Screen 7.0

  glPushMatrix();													// NEW: Prepare Dynamic Transform
  glMultMatrixf(&Transform[0][0]);			  // NEW: Apply Dynamic Transform
  glColor3f(1.0f, 0.75f, 0.75f);
  Sphere(20, 20, 1.3f);
  glPopMatrix();													// NEW: Unapply Dynamic Transform

  //glFlush ();														// Flush The GL Rendering Pipeline
}
