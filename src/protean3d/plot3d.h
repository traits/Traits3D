#pragma once

#include "coordinatesystem.h"
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

    bool prepareDraw();
    void draw();
    void prepareNextDraw();

  private:
    Box hull_;
    CoordinateSystem coordinate_system_;
    GL::Shader shader_;
    GL::VAO vao_;

    glm::mat4 projection_matrix_;
    glm::mat4  modelview_matrix_;
    std::string vertex_shader_src_;
    std::string fragment_shader_src_;

    /**********************************************************************
    * Heightmap vertex and index data
    *********************************************************************/
    std::vector<GLuint> map_line_indices;
    std::vector<std::vector<GLfloat>> map_vertices;

    /* Frustum configuration */
    GLfloat view_angle;
    GLfloat aspect_ratio;
    GLfloat z_near;
    GLfloat z_far;
    void initMatrices();
    void init_map();
    void generate_heightmap_circle(float& center_x, float& center_y, float& size, float& displacement);
    void update_map(size_t num_iter);
    void createBuffers(GLuint program);
  };
} // ns
