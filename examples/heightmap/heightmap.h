#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


class HeightMap
{
public:
  HeightMap();
  virtual ~HeightMap();

  bool prepareDraw();
  void draw();
  void prepareNextDraw();

private:
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

  GLuint make_shader(GLenum type, const char* shader_src);

  /* Frustum configuration */
  GLfloat view_angle;
  GLfloat aspect_ratio;
  GLfloat z_near;
  GLfloat z_far;
  void initMatrices();
  void init_map();
  void generate_heightmap__circle(float* center_x, float* center_y, float* size, float* displacement);
  void update_map(int num_iter);
  GLuint make_shader_program();
  void make_mesh(GLuint program);
};