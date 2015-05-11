/**************************************
*                                     *
*   Jeff Molofee's Basecode Example   *
*          nehe.gamedev.net           *
*                2001                 *
*                                     *
**************************************/

#include <iostream>
#include <windows.h>
#include <gl\gl.h>													// Header File For The OpenGL32 Library
#include <gl\glu.h>													// Header File For The GLu32 Library

#include "math.h"												    // NEW: Needed For Sqrtf
#include "arcball.h"												// NEW: ArcBall Header
#include "Window/Window.h"

#pragma comment( lib, "opengl32.lib" )								// Search For OpenGL32.lib While Linking
#pragma comment( lib, "glu32.lib" )									// Search For GLu32.lib While Linking
//#pragma comment( lib, "glaux.lib" )									// Search For GLaux.lib While Linking
												// We Can Avoid Errors


//inline void printGlError()
//{
//  GLenum err = glGetError();
//
//  switch (err)
//  {
//  case GL_INVALID_ENUM:
//    std::cerr << "GL_INVALID_ENUM" << "\n";
//    break;
//  case GL_INVALID_VALUE:
//    std::cerr << "GL_INVALID_VALUE" << "\n";
//    break;
//  case GL_INVALID_OPERATION:
//    std::cerr << "GL_INVALID_OPERATION" << "\n";
//    break;
//  //case GL_INVALID_FRAMEBUFFER_OPERATION:
//  //  std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION" << "\n";
//  //  break;
//  case GL_OUT_OF_MEMORY:
//    std::cerr << "GL_OUT_OF_MEMORY" << "\n";
//    break;
//  default:
//    std::cerr << "No GL error" << "\n";
//  }
//}



// User Defined Variables
GLUquadricObj *quadratic;											// Used For Our Quadric

const float PI2 = 2.0*3.1415926535f;								// PI Squared

Matrix4fT   Transform   = {  1.0f,  0.0f,  0.0f,  0.0f,				// NEW: Final Transform
                             0.0f,  1.0f,  0.0f,  0.0f,
                             0.0f,  0.0f,  1.0f,  0.0f,
                             0.0f,  0.0f,  0.0f,  1.0f };

Matrix3fT   LastRot     = {  1.0f,  0.0f,  0.0f,					// NEW: Last Rotation
                             0.0f,  1.0f,  0.0f,
                             0.0f,  0.0f,  1.0f };

Matrix3fT   ThisRot     = {  1.0f,  0.0f,  0.0f,					// NEW: This Rotation
                             0.0f,  1.0f,  0.0f,
                             0.0f,  0.0f,  1.0f };

ArcBall    ArcBall(1280.0f, 960.0f);				                // NEW: ArcBall Instance
Point2fT    MousePt;												// NEW: Current Mouse Point
bool        isClicked  = false;										// NEW: Clicking The Mouse?
bool        isRClicked = false;										// NEW: Clicking The Right Mouse Button?
bool        isDragging = false;					                    // NEW: Dragging The Mouse?


BOOL Initialize ()						// Any GL Init Code & User Initialiazation Goes Here
{
  glViewport(0, 0, (GLsizei)(1280), (GLsizei)(960));				// Reset The Current Viewport
  glMatrixMode(GL_PROJECTION);										// Select The Projection Matrix
  glLoadIdentity();													// Reset The Projection Matrix
  gluPerspective(45.0f, (GLfloat)(1280) / (GLfloat)(960),			// Calculate The Aspect Ratio Of The Window
    1.0f, 100.0f);
  glMatrixMode(GL_MODELVIEW);										// Select The Modelview Matrix
  glLoadIdentity();													// Reset The Modelview Matrix

  ArcBall.setBounds((GLfloat)1280, (GLfloat)960);                 //*NEW* Update mouse bounds for arcball

  
  // Start Of User Initialization
    isClicked   = false;								            // NEW: Clicking The Mouse?
    isDragging  = false;							                // NEW: Dragging The Mouse?

	glClearColor (0.0f, 0.0f, 0.0f, 0.5f);							// Black Background
	glClearDepth (1.0f);											// Depth Buffer Setup
	glDepthFunc (GL_LEQUAL);										// The Type Of Depth Testing (Less Or Equal)
	glEnable (GL_DEPTH_TEST);										// Enable Depth Testing
	glShadeModel (GL_FLAT);											// Select Flat Shading (Nice Definition Of Objects)
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);				// Set Perspective Calculations To Most Accurate

	quadratic=gluNewQuadric();										// Create A Pointer To The Quadric Object
	gluQuadricNormals(quadratic, GLU_SMOOTH);						// Create Smooth Normals
	gluQuadricTexture(quadratic, GL_TRUE);							// Create Texture Coords

	glEnable(GL_LIGHT0);											// Enable Default Light
	glEnable(GL_LIGHTING);											// Enable Lighting

	glEnable(GL_COLOR_MATERIAL);									// Enable Color Material

	return TRUE;													// Return TRUE (Initialization Successful)
}

void Deinitialize (void)											// Any User DeInitialization Goes Here
{
	gluDeleteQuadric(quadratic);
}

void Update (DWORD milliseconds)									// Perform Motion Updates Here
{
    if (isRClicked)													// If Right Mouse Clicked, Reset All Rotations
    {
		Matrix3fSetIdentity(&LastRot);								// Reset Rotation
		Matrix3fSetIdentity(&ThisRot);								// Reset Rotation
        Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);		// Reset Rotation
    }

    if (!isDragging)												// Not Dragging
    {
        if (isClicked)												// First Click
        {
			isDragging = true;										// Prepare For Dragging
			LastRot = ThisRot;										// Set Last Static Rotation To Last Dynamic One
			ArcBall.click(&MousePt);								// Update Start Vector And Prepare For Dragging
        }
    }
    else
    {
        if (isClicked)												// Still Clicked, So Still Dragging
        {
            Quat4fT     ThisQuat;

            ArcBall.drag(&MousePt, &ThisQuat);						// Update End Vector And Get Rotation As Quaternion
            Matrix3fSetRotationFromQuat4f(&ThisRot, &ThisQuat);		// Convert Quaternion Into Matrix3fT
            Matrix3fMulMatrix3f(&ThisRot, &LastRot);				// Accumulate Last Rotation Into This One
            Matrix4fSetRotationFromMatrix3f(&Transform, &ThisRot);	// Set Our Final Transform's Rotation From This One
        }
        else														// No Longer Dragging
            isDragging = false;
    }
}

void Torus(float MinorRadius, float MajorRadius)					// Draw A Torus With Normals
{
	int i, j;
	glBegin( GL_TRIANGLE_STRIP );									// Start A Triangle Strip
		for (i=0; i<20; i++ )										// Stacks
		{
			for (j=-1; j<20; j++)									// Slices
			{
				float wrapFrac = (j%20)/(float)20;
				float phi = PI2*wrapFrac;
				float sinphi = float(sin(phi));
				float cosphi = float(cos(phi));

				float r = MajorRadius + MinorRadius*cosphi;

				glNormal3f(float(sin(PI2*(i%20+wrapFrac)/(float)20))*cosphi, sinphi, float(cos(PI2*(i%20+wrapFrac)/(float)20))*cosphi);
				glVertex3f(float(sin(PI2*(i%20+wrapFrac)/(float)20))*r,MinorRadius*sinphi,float(cos(PI2*(i%20+wrapFrac)/(float)20))*r);

				glNormal3f(float(sin(PI2*(i+1%20+wrapFrac)/(float)20))*cosphi, sinphi, float(cos(PI2*(i+1%20+wrapFrac)/(float)20))*cosphi);
				glVertex3f(float(sin(PI2*(i+1%20+wrapFrac)/(float)20))*r,MinorRadius*sinphi,float(cos(PI2*(i+1%20+wrapFrac)/(float)20))*r);
			}
		}
	glEnd();														// Done Torus
}

void Draw (void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear Screen And Depth Buffer
	glLoadIdentity();												// Reset The Current Modelview Matrix
	glTranslatef(-1.5f,0.0f,-6.0f);									// Move Left 1.5 Units And Into The Screen 6.0

    glPushMatrix();													// NEW: Prepare Dynamic Transform
    glMultMatrixf(Transform.M);										// NEW: Apply Dynamic Transform
	glColor3f(0.75f,0.75f,1.0f);
	Torus(0.30f,1.00f);
    glPopMatrix();													// NEW: Unapply Dynamic Transform

	glLoadIdentity();												// Reset The Current Modelview Matrix
	glTranslatef(1.5f,0.0f,-6.0f);									// Move Right 1.5 Units And Into The Screen 7.0

    glPushMatrix();													// NEW: Prepare Dynamic Transform
    glMultMatrixf(Transform.M);										// NEW: Apply Dynamic Transform
	glColor3f(1.0f,0.75f,0.75f);
	gluSphere(quadratic,1.3f,20,20);
    glPopMatrix();													// NEW: Unapply Dynamic Transform

	//glFlush ();														// Flush The GL Rendering Pipeline
}

int main()
{
  // set OpenGL context
  Example::Window w("GLFW OpenGL3 Arcball Demo", 1, 2);
  //if (!hm.initializeGL())
  //  return false;

  Initialize();

  //if (!hm.loadData())
  //  return -1;

  //hm.setRotation(30, 0, 45);
  //hm.setBackgroundColor(Traits3D::Color(1, 1, 1, 1));

  /* main loop */
  double last_update_time = glfwGetTime();

  while (!w.onClose())
  {

    /* Check the frame rate and update the heightmap if needed */
    double dt = glfwGetTime();
    //if ((dt - last_update_time) > 0.1)
    {
      MousePt.s.X = w.xPos();
      MousePt.s.Y = w.yPos();
      isClicked = w.isMousePressing();
      Update(0);
      Draw();
      //hm.draw();
      w.update();
      /* generate the next iteration of the heightmap */
      last_update_time = dt;
    }
  }
  return 0;
}
