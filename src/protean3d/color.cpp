#include <cmath>
#include "helper.h"
#include "color.h"


Protean3D::RGBA Protean3D::Color::color(float z, ColorVector const& vec, float zmin, float zmax)
{
  size_t len = vec.size();

  if (z<zmin || z>zmax || zmax <= zmin || 0==len)
    return RGBA();

  size_t idx = static_cast<size_t>(std::lround((z - zmin) / (zmax - zmin) * len));

  return (idx < len) ? vec[idx] : vec.back();
}

Protean3D::ColorVector Protean3D::Color::stdColor(size_t len)
{
  if (0 == len)
    return ColorVector();

  ColorVector colors(len);

  float fsize = static_cast<float>(len);
  for (auto i = 0; i != len; ++i)
  {
    glm::vec4& elem = colors[i];
    elem.r = i / fsize;
    elem.g = i / fsize / 4;
    elem.b = 1 - i / fsize;
    elem.a = 1.0f;
  }

  return colors;
}

Protean3D::ColorVector Protean3D::Color::createColors(std::vector<glm::vec3> const& data, ColorVector const& color_field)
{
  ColorVector ret(data.size());

  Box hull = calcHull(data);

  float zmin = static_cast<float>(hull.minVertex.z);
  float zmax = static_cast<float>(hull.maxVertex.z);

  for (auto i = 0; i != data.size(); ++i)
  {
    RGBA c = color(data[i].z, color_field, zmin, zmax);
    ret[i] = c;
  }
  return ret;
}
