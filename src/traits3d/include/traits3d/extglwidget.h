#pragma once

#include "traits3d/types.h"
#include "glb/glhelper.h"
#include "traits3d/light.h"

namespace traits3d
{
/**
The class covers mouse/keyboard handling, lighting and basic transformations, like
scaling, shifting and rotating objects.
*/
class TRAITS3D_EXPORT ExtGLWidget
{
public:
    ExtGLWidget();
    virtual ~ExtGLWidget() {}

    bool isInitialized() const
    {
        return gl_is_initialized_p;
    }
    virtual bool initializeGL();
    virtual void draw() = 0;
    virtual void updateData() = 0;


    // transformations

    float xRotation() const
    {
        return xRot_;   //!< Returns rotation around X axis [0..2PI]
    }
    float yRotation() const
    {
        return yRot_;   //!< Returns rotation around Y axis [0..2PI]
    }
    float zRotation() const
    {
        return zRot_;   //!< Returns rotation around Z axis [0..2PI]
    }

    float xShift() const
    {
        return xShift_;   //!< Returns shift along X axis (object coordinates)
    }
    float yShift() const
    {
        return yShift_;   //!< Returns shift along Y axis (object coordinates)
    }
    float zShift() const
    {
        return zShift_;   //!< Returns shift along Z axis (object coordinates)
    }

    float xViewportShift() const
    {
        return xVPShift_;   //!< Returns relative shift [-1..1] along X axis (view coordinates)
    }
    float yViewportShift() const
    {
        return yVPShift_;   //!< Returns relative shift [-1..1] along Y axis (view coordinates)
    }

    float xScale() const
    {
        return xScale_;   //!< Returns scaling for X values [0..inf]
    }
    float yScale() const
    {
        return yScale_;   //!< Returns scaling for Y values [0..inf]
    }
    float zScale() const
    {
        return zScale_;   //!< Returns scaling for Z values [0..inf]
    }

    float zoom() const
    {
        return zoom_;   //!< Returns zoom (0..inf)
    }
    bool ortho() const
    {
        return ortho_;    //!< Returns orthogonal (true) or perspective (false) projection
    }

    // lighting

    bool lightingEnabled() const; //!< Returns true, if Lighting is enabled, false else
    //! Turn light on
    void illuminate(size_t light = 0);
    //! Turn light off
    void blowout(size_t light = 0);

    void setMaterialComponent(GLenum property, float r, float g, float b, float a = 1.0);
    void setMaterialComponent(GLenum property, float intensity);
    void setShininess(float exponent);
    void setLightComponent(GLenum property, float r, float g, float b, float a = 1.0, unsigned light = 0);
    void setLightComponent(GLenum property, float intensity, unsigned light = 0);

    bool setRotation(float xVal, float yVal, float zVal);
    bool setShift(float xVal, float yVal, float zVal);
    bool setViewportShift(float xVal, float yVal);
    bool setScale(float xVal, float yVal, float zVal);
    bool setZoom(float);
    bool setOrtho(bool);

    void enableLighting(bool val = true); //!< Turn Lighting on or off
    void appendLight(std::shared_ptr<Light> val);

protected:
    bool gl_is_initialized_p = false;
    void applyLights();

private:
    //bool init_glloader();

    // trafos
    float xRot_, yRot_, zRot_, xShift_, yShift_, zShift_, zoom_
    , xScale_, yScale_, zScale_, xVPShift_, yVPShift_;

    bool ortho_;

    std::vector<std::shared_ptr<Light>> lights_;
    void applyLight(unsigned idx);

    static const float eps_;
};
} // ns


