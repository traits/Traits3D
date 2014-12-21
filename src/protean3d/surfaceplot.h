#pragma once

#include "plot3d.h"

namespace Protean3D
{
  class PROTEAN3D_EXPORT SurfacePlot : public Plot3D
  {
  public:
    bool addPositionData(std::vector<glm::vec3> const& data,
      size_t xsize, size_t ysize, GLenum drawtype = GL_STATIC_DRAW);

    bool updatePositionData(std::vector<glm::vec3> const& data);
    bool addDataColor(ColorVector const& val);
    ColorVector createColors(std::vector<glm::vec3> const& data, ColorVector const& color_field);
    bool addMeshColor(glm::vec4 const& val);

  private:
  };
} // ns