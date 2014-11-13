#pragma once

#include "protean3d/plot3d.h"

class HeightMap : public Protean3D::Plot3D
{
public:
  HeightMap();
  bool loadData();
  bool updateAfter() override;
private:
  std::vector<GLuint> map_line_indices;
  std::array<std::vector<GLfloat>, 3> map_vertices;

  void init_map();

  void generate_heightmap_circle(float& center_x, float& center_y, float& size, float& displacement);
  void update_map(size_t num_iter);
};