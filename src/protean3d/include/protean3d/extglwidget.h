#pragma once

#include "protean3d/types.h"
#include "protean3d/glbase/glhelper.h"

namespace Protean3D
{
  
/**
  The class covers mouse/keyboard handling, lighting and basic transformations, like
  scaling, shifting and rotating objects.
*/
class PROTEAN3D_EXPORT ExtGLWidget 
{
public:
  ExtGLWidget ();
  virtual ~ExtGLWidget() {}
	
  bool isInitialized() const { return gl_is_initialized_p; }
  virtual bool initializeGL();
  virtual void draw() = 0;
  virtual void updateData() = 0;


  // transformations
  
	float xRotation() const { return xRot_;}  //!< Returns rotation around X axis [-360..360] (some angles are equivalent)
	float yRotation() const { return yRot_;}  //!< Returns rotation around Y axis [-360..360] (some angles are equivalent)
	float zRotation() const { return zRot_;}  //!< Returns rotation around Z axis [-360..360] (some angles are equivalent)

	float xShift() const { return xShift_;} //!< Returns shift along X axis (object coordinates)
	float yShift() const { return yShift_;} //!< Returns shift along Y axis (object coordinates)
	float zShift() const { return zShift_;} //!< Returns shift along Z axis (object coordinates)
	
	float xViewportShift() const { return xVPShift_;} //!< Returns relative shift [-1..1] along X axis (view coordinates)
	float yViewportShift() const { return yVPShift_;} //!< Returns relative shift [-1..1] along Y axis (view coordinates)
	
	float xScale() const { return xScale_;} //!< Returns scaling for X values [0..inf]
	float yScale() const { return yScale_;} //!< Returns scaling for Y values [0..inf]
	float zScale() const { return zScale_;} //!< Returns scaling for Z values [0..inf]

	float zoom() const { return zoom_;} //!< Returns zoom (0..inf)
	bool ortho() const { return ortho_; } //!< Returns orthogonal (true) or perspective (false) projection 
  
  // lighting

  bool lightingEnabled() const; //!< Returns true, if Lighting is enabled, false else
  //! Turn light on
  void illuminate(unsigned light = 0);
  //! Turn light off
  void blowout(unsigned light = 0);

  void setMaterialComponent(GLenum property, float r, float g, float b, float a = 1.0);    
  void setMaterialComponent(GLenum property, float intensity);    
  void setShininess(float exponent);
  void setLightComponent(GLenum property, float r, float g, float b, float a = 1.0, unsigned light=0);    
  void setLightComponent(GLenum property, float intensity, unsigned light=0);    
  //! Returns Light 'idx' rotation around X axis [-360..360] (some angles are equivalent)
  float xLightRotation(unsigned idx = 0) const { return (idx<8) ? lights_[idx].rot.x : 0;}
  //! Returns Light 'idx' rotation around Y axis [-360..360] (some angles are equivalent)
  float yLightRotation(unsigned idx = 0) const { return (idx<8) ? lights_[idx].rot.y : 0;}
  //! Returns Light 'idx' rotation around Z axis [-360..360] (some angles are equivalent)
  float zLightRotation(unsigned idx = 0) const { return (idx<8) ? lights_[idx].rot.z : 0;}
  //! Returns shift of Light 'idx 'along X axis (object coordinates)
  float xLightShift(unsigned idx = 0) const {return (idx<8) ? lights_[idx].shift.x : 0;} 
  //! Returns shift of Light 'idx 'along Y axis (object coordinates)
  float yLightShift(unsigned idx = 0) const {return (idx<8) ? lights_[idx].shift.y : 0;} 
  //! Returns shift of Light 'idx 'along Z axis (object coordinates)
  float zLightShift(unsigned idx = 0) const {return (idx<8) ? lights_[idx].shift.z : 0;}

	bool setRotation( float xVal, float yVal, float zVal ); 																														
	bool setShift( float xVal, float yVal, float zVal );    																														
	bool setViewportShift( float xVal, float yVal );         																														
	bool setScale( float xVal, float yVal, float zVal );    																														
	bool setZoom( float );                                    																														
  bool setOrtho(bool);                                       																														
  
  void enableLighting(bool val = true); //!< Turn Lighting on or off
  void disableLighting(bool val = true); //!< Turn Lighting on or off
  //! Rotate lightsource[idx]
  void setLightRotation( float xVal, float yVal, float zVal, unsigned int idx = 0 ); 																														
  //! Shift lightsource[idx]
	void setLightShift( float xVal, float yVal, float zVal, unsigned int idx = 0 );    																														

protected:
  bool gl_is_initialized_p = false;
  void applyLights();

private:
  //bool init_glloader();

  // trafos  
  float xRot_, yRot_, zRot_, xShift_, yShift_, zShift_, zoom_
           , xScale_, yScale_, zScale_, xVPShift_, yVPShift_;
	
	bool ortho_;
	
  // lighting
  struct Light
  {  
    Light() : unlit(true){}
    bool unlit;  
    Protean3D::TripleF rot;
    Protean3D::TripleF shift;
  };
  std::vector<Light> lights_;
  bool lighting_enabled_;
  void applyLight(unsigned idx);

  static const float eps_;
};


} // ns


