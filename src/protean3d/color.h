#pragma once

#include "types.h"

namespace Protean3D
{
class PROTEAN3D_EXPORT Color
{
public:
  virtual ~Color(){}
  static RGBA color(float z, ColorVector const& vec, float zmin, float zmax);
  static ColorVector stdColor(size_t len);
  static ColorVector createColors(std::vector<glm::vec3> const& data, ColorVector const& color_field);

private:
};

} // ns


