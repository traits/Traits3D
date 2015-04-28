#pragma once

#include "traits3d/surfaceplot.h"

class HeightMap : public Traits3D::SurfacePlot
{
public:
  HeightMap();
  bool loadData();
  void updateData() override;

private:
  //std::vector<GLuint> map_line_indices;
  Traits3D::MatrixF map_vertices;

  void init_map();

  void generate_heightmap_circle(float& center_x, float& center_y, float& size, float& displacement);
  void update_map(size_t num_iter);
};