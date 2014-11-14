#pragma once


#include <array>
#include "coordinatesystem.h"
#include "shadermill.h"
#include "shader.h"
#include "vao.h"

namespace Protean3D
{
  //! Base class for all plotting widgets
  /*!
    Plot3D handles all the common features for plotting widgets beyond the low-level extensions of
    ExtGLWidget - coordinate system, labeling and more. It contains some pure virtual functions and is -
    in this respect - an abstract base class. It's nevertheless no pure interface.
    The class provides interfaces for basic data controlled color allocation.
    */
  class PROTEAN3D_EXPORT Plot3D/* : public ExtGLWidget*/
  {
  public:
    Plot3D();
    virtual ~Plot3D();


    void draw();
    virtual bool updateAfter(){ return true; }

    bool addPositionData(std::vector<glm::vec3> const& data, GLenum drawmode);

    bool addPositionData(std::array<std::vector<float>, 3> const& data, 
      size_t xsize, size_t ysize,
      GLenum xdrawtype = GL_STATIC_DRAW,
      GLenum ydrawtype = GL_STATIC_DRAW,
      GLenum zdrawtype = GL_STATIC_DRAW);

    // index in [0..2] and only for 2nd variant of addPositionData
    bool updatePositionData(short index, std::vector<float> const& data);

    bool addColorData(std::vector<glm::vec3> const& data);
    
  private:
    Protean3D::GL::ShaderMill shader_mill_;
    Box hull_;
    CoordinateSystem coordinate_system_;
    GL::Shader shader_;
    GL::VAO vao_;

    glm::mat4 projection_matrix_;
    glm::mat4  modelview_matrix_;

    /**********************************************************************
    * Heightmap vertex and index data
    *********************************************************************/

    /* Frustum configuration */
    GLfloat view_angle;
    GLfloat aspect_ratio;
    GLfloat z_near;
    GLfloat z_far;
  };
} // ns
