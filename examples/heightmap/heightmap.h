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
  GLuint make_shader_program();

  void init_map(void);
  void generate_heightmap__circle(float* center_x, float* center_y, float* size, float* displacement);
  void update_map(int num_iter);
  void make_mesh(GLuint program);
  void update_mesh(void);

  GLsizei numLines() const;
  
  std::vector<GLfloat> projection_matrix;
  std::vector<GLfloat> modelview_matrix;
  std::string default_vertex_shader;
  std::string default_fragment_shader;

  /* Frustum configuration */
  GLfloat view_angle;
  GLfloat aspect_ratio;
  GLfloat z_near;
  GLfloat z_far;

private:
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
};