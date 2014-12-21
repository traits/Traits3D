#pragma once

#include <array>
#include "colortable.h"
#include "coordinatesobject.h"
#include "dataobject.h"
#include "extglwidget.h"


namespace Protean3D
{
  //! Base class for all plotting widgets
  /*!
    Plot3D handles all the common features for plotting widgets beyond the low-level extensions of
    ExtGLWidget - coordinate system, labeling and more. It contains some pure virtual functions and is -
    in this respect - an abstract base class. It's nevertheless no pure interface.
    The class provides interfaces for basic data controlled color allocation.
    */
  class PROTEAN3D_EXPORT Plot3D : public ExtGLWidget
  {
  public:
    Plot3D();
    virtual ~Plot3D();


    void draw();
    void updateData() override {}

  protected:
    Box hull_p;
    GL::CoordinatesObject coordinates_object_p;
    GL::DataObject data_object_p;

    glm::mat4 projection_matrix_p;
    glm::mat4  modelview_matrix_p;

  private:
    /* Frustum configuration */
    GLfloat view_angle;
    GLfloat aspect_ratio;
    GLfloat z_near;
    GLfloat z_far;
  };
} // ns
