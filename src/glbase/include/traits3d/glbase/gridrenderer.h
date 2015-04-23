#pragma once

#include <memory>
#include <map>
#include "traits3d/types.h"
#include "traits3d/glbase/globject.h"

namespace Traits3D
{
  namespace GL
  {
    class GridRenderer : public GL::Object
    {
    public:
      static const char* VertexCode;
      static const char* FragmentCode;

      GridRenderer();
      
      void setColor(Color const& val) { color_ = val; }

      bool createData(
        std::vector<TripleF> const& start_u, std::vector<TripleF> const& stop_u,
        std::vector<TripleF> const& start_v, std::vector<TripleF> const& stop_v);

      void draw(Transformation const& matrices) override;
    
    private:
      Shader shader_;
      std::unique_ptr<VBO> vbo_;
      std::vector<TripleF> vbo_data_;
      Color color_ = Color(0, 0, 0, 1);
    };
  } // ns
} // ns