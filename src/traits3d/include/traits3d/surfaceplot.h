#pragma once

#include "traits3d/matrix.h"
#include "plot3d.h"

namespace Traits3D
{
  class TRAITS3D_EXPORT SurfacePlot : public Plot3D
  {
    public:
      bool initializeGL() override;
      bool addPositionData(std::vector<TripleF> const& data,
        size_t xsize, size_t ysize, GLenum drawtype = GL_STATIC_DRAW);
      bool addPositionData(Traits3D::MatrixF const& data, GLenum drawtype = GL_STATIC_DRAW);

      bool updatePositionData(std::vector<TripleF> const& data);
      bool setDataColor(ColorVector const& val);
      ColorVector createColors(std::vector<TripleF> const& data, ColorVector const& color_field);
      bool setMeshColor(Color const& val);
  };
} // ns