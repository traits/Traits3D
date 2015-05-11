#if defined(_MSC_VER) /* MSVC Compiler */
#pragma warning ( disable : 4305 )
#pragma warning ( disable : 4786 )
#endif

#include <cmath>
#include "traits3d/helper.h"
#include "traits3d/extglwidget.h"

using namespace std;

#ifndef WHEEL_DELTA
#define WHEEL_DELTA 120
#endif

namespace {
//inline GLenum lightEnum(unsigned idx)
//{
//  switch(idx) {
//  case 0:
//    return GL_LIGHT0;
//  case 1:
//    return GL_LIGHT1;
//  case 2:
//    return GL_LIGHT2;
//  case 3:
//    return GL_LIGHT3;
//  case 4:
//    return GL_LIGHT4;
//  case 5:
//    return GL_LIGHT5;
//  case 6:
//    return GL_LIGHT6;
//  case 7:
//    return GL_LIGHT7;
//  default:
//    return GL_LIGHT0;
//  }
//}
}

const float Traits3D::ExtGLWidget::eps_ = std::numeric_limits<float>::epsilon();

/*!
  This should be the first call in your derived classes constructors.
*/
Traits3D::ExtGLWidget::ExtGLWidget()
{
  xRot_ = yRot_ = zRot_ = 0.0f;   // default object rotation

  xShift_ = yShift_ = zShift_ = xVPShift_ = yVPShift_ = 0.0f;
  xScale_ = yScale_ = zScale_ = 1.0f;
  zoom_ = 1;
  ortho_ = true;

  lighting_enabled_ = false;
  disableLighting();
  lights_ = std::vector<Light>(8);
}

/**
  Set the rotation angle of the object. If you look along the respective axis towards ascending values,
  the rotation is performed in mathematical \e negative sense
  \param xVal angle in \e degree to rotate around the X axis
  \param yVal angle in \e degree to rotate around the Y axis
  \param zVal angle in \e degree to rotate around the Z axis
*/
bool Traits3D::ExtGLWidget::setRotation( float xVal, float yVal, float zVal )
{
  if (xRot_ == xVal && yRot_ == yVal && zRot_ == zVal)
    return false;

  xRot_ = xVal;
  yRot_ = yVal;
  zRot_ = zVal;

  return true;
}

/**
  Set the shift in object (world) coordinates.
  \param xVal shift along (world) X axis
  \param yVal shift along (world) Y axis
  \param zVal shift along (world) Z axis
  \see setViewportShift()
*/
bool Traits3D::ExtGLWidget::setShift( float xVal, float yVal, float zVal )
{
  if (xShift_ == xVal && yShift_ == yVal && zShift_ == zVal)
    return false;

  xShift_ = xVal;
  yShift_ = yVal;
  zShift_ = zVal;

  return true;
}

/**
  Performs shifting along screen axes.
  The shift moves points inside a sphere,
  which encloses the unscaled and unzoomed data
  by multiples of the spheres diameter

  \param xVal shift along (view) X axis
  \param yVal shift along (view) Y axis
  \see setShift()
*/
bool Traits3D::ExtGLWidget::setViewportShift( float xVal, float yVal )
{
  if (xVPShift_ == xVal && yVPShift_ == yVal)
    return false;

  xVPShift_ = xVal;
  yVPShift_ = yVal;

  return true;
}

/**
  Set the scale in object (world) coordinates.
  \param xVal scaling for X values
  \param yVal scaling for Y values
  \param zVal scaling for Z values

  A respective value of 1 represents no scaling;
*/
bool Traits3D::ExtGLWidget::setScale( float xVal, float yVal, float zVal )
{
  if (xScale_ == xVal && yScale_ == yVal && zScale_ == zVal)
    return false;

  xScale_ = (xVal < eps_ ) ? eps_ : xVal;
  yScale_ = (yVal < eps_ ) ? eps_ : yVal;
  zScale_ = (zVal < eps_ ) ? eps_ : zVal;

  return true;
}

/**
  Set the (zoom in addition to scale).
  \param val zoom value (value == 1 indicates no zooming)
*/
bool Traits3D::ExtGLWidget::setZoom( float val )
{
  if (zoom_ == val)
    return false;

  zoom_ = (val < eps_) ? eps_ : val;

  return true;
}

/*!
  Set up ortogonal or perspective mode and updates widget
*/
bool Traits3D::ExtGLWidget::setOrtho( bool val )
{
  if (val == ortho_)
    return false;

  ortho_ = val;

  return true;
}

/*!
  Set up the OpenGL rendering state
*/
bool Traits3D::ExtGLWidget::initializeGL()
{
  if (gl_is_initialized_p)
    return true;

  //if (!init_glloader())
  //{
  //  initializedGL_ = false;
  //  return false;
  //}

  glPolygonOffset(1, 1);
  glEnable(GL_POLYGON_OFFSET_FILL);
  //todo enable this, we need it for correct hidden lines etc. (implement something
  // better than glPolygonOffset
  // e.g. https://www.opengl.org/discussion_boards/showthread.php/179958-How-to-draw-one-line-on-top-of-another-in-OpenGL-without-Z-fighting?p=1245277&viewfull=1#post1245277
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glEnable(GL_LINE_SMOOTH);
  //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

  // Set up the lights

  disableLighting();

  GLfloat whiteAmb[4] = {1.0, 1.0, 1.0, 1.0};

  setLightShift(0, 0, 3000);
// glEnable(GL_COLOR_MATERIAL);

  //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteAmb);

// setMaterialComponent(GL_DIFFUSE, 1.0);
// setMaterialComponent(GL_SPECULAR, 0.3);
// setMaterialComponent(GL_SHININESS, 5.0);
// setLightComponent(GL_DIFFUSE, 1.0);
// setLightComponent(GL_SPECULAR, 1.0);

  gl_is_initialized_p = true;
  return true;
}

void Traits3D::ExtGLWidget::enableLighting(bool val)
{
  //if (lighting_enabled_ == val)
  //  return;
  //
  //lighting_enabled_ = val;
  ////makeCurrent();
  //if (val)
  //  glEnable(GL_LIGHTING);
  //else
  //  glDisable(GL_LIGHTING);
}

void Traits3D::ExtGLWidget::disableLighting(bool val)
{
  enableLighting(!val);
}

bool Traits3D::ExtGLWidget::lightingEnabled() const
{
  return lighting_enabled_;
}

/**
  \param light light number [0..7]
  \see setLight
*/
void Traits3D::ExtGLWidget::illuminate(unsigned light)
{
  if (light>7)
    return;
  lights_[light].unlit = false;
}
/**
  \param light light number [0..7]
  \see setLight
*/
void Traits3D::ExtGLWidget::blowout(unsigned light)
{
  if (light>7)
    return;
  lights_[light].unlit = false;
}

/**
  Sets GL material properties
*/
void Traits3D::ExtGLWidget::setMaterialComponent(GLenum property, float r, float g, float b, float a)
{
  //GLfloat rgba[4] = {(GLfloat)r, (GLfloat)g, (GLfloat)b, (GLfloat)a};
  ////makeCurrent();
  //glMaterialfv(GL_FRONT_AND_BACK, property, rgba);
}

/**
  This function is for convenience. It sets GL material properties with the equal r,g,b values
  and a blending alpha with value 1.0
*/
void Traits3D::ExtGLWidget::setMaterialComponent(GLenum property, float intensity)
{
  setMaterialComponent(property,intensity,intensity,intensity,1.0);
}

/**
  Sets GL shininess
*/
void Traits3D::ExtGLWidget::setShininess(float exponent)
{
  ////makeCurrent();
  //glMaterialf(GL_FRONT, GL_SHININESS, static_cast<GLfloat>(exponent));
}

/**
  Sets GL light properties for light 'light'
*/
void Traits3D::ExtGLWidget::setLightComponent(GLenum property, float r, float g, float b, float a, unsigned light)
{
  //GLfloat rgba[4] = {(GLfloat)r, (GLfloat)g, (GLfloat)b, (GLfloat)a};
  ////makeCurrent();
  //glLightfv(lightEnum(light), property, rgba);
}

/**
  This function is for convenience. It sets GL light properties with the equal r,g,b values
  and a blending alpha with value 1.0
*/
void Traits3D::ExtGLWidget::setLightComponent(GLenum property, float intensity, unsigned light)
{
  //setLightComponent(property,intensity,intensity,intensity,1.0, lightEnum(light));
}

/**
  Set the rotation angle of the light source. If you look along the respective axis towards ascending values,
  the rotation is performed in mathematical \e negative sense
  \param xVal angle in \e degree to rotate around the X axis
  \param yVal angle in \e degree to rotate around the Y axis
  \param zVal angle in \e degree to rotate around the Z axis
  \param light light number
*/
void Traits3D::ExtGLWidget::setLightRotation( float xVal, float yVal, float zVal, unsigned light )
{
  if (light>7)
    return;
  lights_[light].rot.x = xVal;
  lights_[light].rot.y = yVal;
  lights_[light].rot.z = zVal;
}

/**
  Set the shift in light source (world) coordinates.
  \param xVal shift along (world) X axis
  \param yVal shift along (world) Y axis
  \param zVal shift along (world) Z axis
  \param light light number
  \see setViewportShift()
*/
void Traits3D::ExtGLWidget::setLightShift( float xVal, float yVal, float zVal, unsigned light )
{
  if (light>7)
    return;
  lights_[light].shift.x = xVal;
  lights_[light].shift.y = yVal;
  lights_[light].shift.z = zVal;
}


bool Traits3D::ExtGLWidget::setRotation(TripleF const& axis, float angle, bool normalize_axis/* = true*/)
{
  if (isZero(axis.length()))
    return false;
  
  rot_axis_ = (normalize_axis) ? glm::normalize(axis) : axis;

  // normalize to [0,2PI]
  angle = std::fmod(angle, static_cast<float>(2 * Traits3D::PI));
  if (angle < 0)
    angle = static_cast<float>(2 * Traits3D::PI) + angle;

  return true;
}

void Traits3D::ExtGLWidget::applyLight(unsigned light)
{
  //if (lights_[light].unlit)
//   return;

// glEnable(lightEnum(light));
// glLoadIdentity();
//
// glRotated( lights_[light].rot.x-90, 1.0, 0.0, 0.0 );
// glRotated( lights_[light].rot.y   , 0.0, 1.0, 0.0 );
// glRotated( lights_[light].rot.z   , 0.0, 0.0, 1.0 );
// GLfloat lightPos[4] = {
//   static_cast<GLfloat>(lights_[light].shift.x),
//   static_cast<GLfloat>(lights_[light].shift.y),
//   static_cast<GLfloat>(lights_[light].shift.z),
//   1.0f};
// GLenum le = lightEnum(light);
// glLightfv(le, GL_POSITION, lightPos);
}

void Traits3D::ExtGLWidget::applyLights()
{
// glMatrixMode( GL_MODELVIEW );
  //glPushMatrix();
// for (unsigned i=0; i<8; ++i)
// {
//   applyLight(i);
// }
// glPopMatrix();
}

//bool Traits3D::ExtGLWidget::init_glloader()
//{
//  // Initialize glloader
//
//  return (ogl_LoadFunctions() == ogl_LOAD_FAILED) ? false : true;
//}
