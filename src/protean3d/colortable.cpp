#include <cmath>
#include "protean3d/helper.h"
#include "protean3d/colortable.h"

// reconciles with insufficient Android NDK (mingw) implementation
// " 'lround' not member of 'std'"
using namespace std;

Protean3D::Color Protean3D::ColorTable::color(float z, ColorVector const& vec, float zmin, float zmax)
{
  size_t len = vec.size();

  if (z<zmin || z>zmax || zmax <= zmin || 0==len)
    return Color();

  size_t idx = static_cast<size_t>(lround((z - zmin) / (zmax - zmin) * len));

  return (idx < len) ? vec[idx] : vec.back();
}

Protean3D::ColorVector Protean3D::ColorTable::stdColor(size_t len)
{
  if (0 == len)
    return ColorVector();

  ColorVector colors(len);

  float fsize = static_cast<float>(len);
  for (size_t i = 0; i != len; ++i)
  {
    Color& elem = colors[i];
    elem.r = i / fsize;
    elem.g = i / fsize / 4;
    elem.b = 1 - i / fsize;
    elem.a = 1.0f;
  }

  return colors;
}

Protean3D::ColorVector Protean3D::ColorTable::createColors(TripleVector const& data, ColorVector const& color_field)
{
  ColorVector ret(data.size());

  Box hull = calculateBox(data);

  float zmin = static_cast<float>(hull.minVertex.z);
  float zmax = static_cast<float>(hull.maxVertex.z);

  for (size_t i = 0; i != data.size(); ++i)
  {
    Color c = color(static_cast<float>(data[i].z), color_field, zmin, zmax);
    ret[i] = c;
  }
  return ret;
}
