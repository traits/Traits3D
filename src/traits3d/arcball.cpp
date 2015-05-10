#define _USE_MATH_DEFINES

#include <algorithm>
#include "traits3d/arcball.h"

const float Arcball::INITIAL_FOV = 30;
const float Arcball::TRANSLATION_FACTOR = 0.01f;


/**
 * Default constructor, it sets the ballRadius to 600
**/
Arcball::Arcball()
{  this->ballRadius=600;
   isRotating=false;
   width=height=0;
   reset();
}

/**
* Set width and height of the current windows, it's needed every time you resize the window
* \param w Width of the rendering window
* \param h Height of the rendering window
 **/
void Arcball::setWidthHeight(int w, int h)
{  width=w;
   height=h;
   ballRadius = std::min((int)(w/2), (int)(h/2));
}

/**
* Set the radius of the ball (a typical radius for a 1024x768 window is 600
* \param newRadius The radius of the spherical dragging area
 **/
void Arcball::setRadius(float newRadius)
{  ballRadius = newRadius;
}

/**
* Start the rotation. Use this method in association with the left click.
* Here you must give directly the coordinates of the mouse as the glut functions extract. This method supposes that the 0,0 is in the upper-left part of the screen
* \param _x Horizontal position of the mouse (0,0) = upper left corner (w,h) = lower right
* \param _y Vertical position of the mouse (0,0) = upper left corner (w,h) = lower right
 *
**/
void Arcball::startRotation(int _x, int _y)
{  int x = ( (_x)-(width/2) );
   int y = ((height/2)-_y);

   startRotationVector = convertXY(x,y);

   currentRotationVector=  startRotationVector;
   isRotating = true;
}

/**
* Update the rotation. Use this method in association with the drag event.
* Here you must give directly the coordinates of the mouse as the glut functions extract. This method supposes that the 0,0 is in the upper-left part of the screen
* \param _x Horizontal position of the mouse (0,0) = upper left corner (w,h) = lower right
* \param _y Vertical position of the mouse (0,0) = upper left corner (w,h) = lower right
**/
void Arcball::updateRotation(int _x, int _y)
{  int x = ( (_x)-(width/2) );
   int y = ((height/2)-_y);

   currentRotationVector = convertXY(x,y);
}

/**
* Apply the computed rotation matrix
* This method must be invoked inside the \code glutDisplayFunc() \endcode
*
**/
void Arcball::applyRotationMatrix()
{  if (isRotating)
   {  // Do some rotation according to start and current rotation vectors
      //cerr << currentRotationVector.transpose() << " " << startRotationVector.transpose() << endl;
      if ( ( currentRotationVector - startRotationVector).length() > 1E-6 )
      {  
         glm::vec3 rotationAxis = glm::normalize(glm::cross(currentRotationVector, startRotationVector));

         double val = glm::dot(currentRotationVector, startRotationVector);
         val > (1-1E-10) ? val=1.0 : val=val ;
         double rotationAngle = acos(val) * 180.0f/(float)M_PI;

         // rotate around the current position
         applyTranslationMatrix(true);
         glRotatef(rotationAngle * 2, -rotationAxis.x(),  -rotationAxis.y(),-rotationAxis.z());
         applyTranslationMatrix(false);
      }
   }
   glMultMatrixf(startMatrix);
}

/**
* Stop the current rotation and prepare for a new click-then-drag event
*
**/
void Arcball::stopRotation()
{

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   applyRotationMatrix();
   // set the current matrix as the permanent one
   glGetFloatv(GL_MODELVIEW_MATRIX, startMatrix);
   isRotating = false;
}


/**
* Apply the translation matrix to the current transformation (zoom factor)
**/
void Arcball::applyTranslationMatrix(bool reverse)
{  float factor = (reverse?-1.0f:1.0f);
   float tx = transX + (currentTransX - startTransX)*TRANSLATION_FACTOR;
   float ty = transY + (currentTransY - startTransY)*TRANSLATION_FACTOR;
   glTranslatef(factor*tx,  factor*(-ty), 0);
}

/**
* Maps the mouse coordinates to points on a sphere, if the points lie outside the sphere, the z is 0, otherwise is \f$ \sqrt(r^2 - (x^2+y^2) ) \f$ where \f$ x,y \f$
* are the window centric coordinates of the mouse
* \param x Mouse x coordinate
* \param y Mouse y coordinate
**/
glm::vec3 Arcball::convertXY(int x, int y)
{

   int d = x*x+y*y;
   float radiusSquared = ballRadius*ballRadius;
   if (d > radiusSquared)
   {
     return glm::normalize(glm::vec3((float)x, (float)y, 0));
   }
   else
   {
     return glm::normalize(glm::vec3((float)x, (float)y, sqrt(radiusSquared - d)));
   }
}

/**
 * Reset the current transformation to the identity
**/
void Arcball::reset()
{  
  fov = INITIAL_FOV;
  
  startMatrix = glm::mat4(1);
  transX = transY = 0;
  startTransX = startTransY = currentTransX = currentTransY = 0;
}
