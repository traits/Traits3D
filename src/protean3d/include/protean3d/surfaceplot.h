#pragma once

#include "plot3d.h"

namespace Protean3D
{
  class PROTEAN3D_EXPORT SurfacePlot : public Plot3D
  {
    public:
      bool initializeGL() override;
      bool addPositionData(std::vector<TripleF> const& data,
                           size_t xsize, size_t ysize, GLenum drawtype = GL_STATIC_DRAW);

      bool updatePositionData(std::vector<TripleF> const& data);
      bool addDataColor(ColorVector const& val);
      ColorVector createColors(std::vector<TripleF> const& data, ColorVector const& color_field);
      bool addMeshColor(Color const& val);
  };
} // ns