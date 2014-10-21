#pragma once

#include "coordinatesystem.h"
#include "shader.h"

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
    Protean3D::Box hull_;
    Protean3D::CoordinateSystem coordinate_system_;
    Protean3D::GL::Shader shader_;

    std::vector<GLfloat> projection_matrix;
    std::vector<GLfloat> modelview_matrix;
    std::string default_vertex_shader;
    std::string default_fragment_shader;

    /* Store uniform location for the shaders
    * Those values are setup as part of the process of creating
    * the shader program. They should not be used before creating
    * the program.
    */
    GLuint mesh;
    GLuint mesh_vbo[4];

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
