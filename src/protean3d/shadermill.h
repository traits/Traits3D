#pragma once

#include <string>
#include "global.h"

namespace Protean3D
{
  namespace GL
  {
    enum class VertexShaderCategory
    {
      Triangles,
      Lines
    };

    //! Creates shader source texts
    class ShaderMill
    {
    public:
      static const std::string proj_matrix;
      static const std::string mv_matrix;
      static const std::string v_in_color;
      static const std::string v_coordinates;
      static const std::string v_normals;

      ShaderMill();
      std::string vertexCode(VertexShaderCategory val) const;
      std::string fragmentCode() const;

    private:
      static const std::string os_switch_;
      static const std::string matrix_preamble_;
      static const std::string main_begin_;
      static const std::string main_end_;

      std::string v_standard_txt_;
      std::string f_standard_txt_;

      std::string lineText() const;
    };

  } // ns
} // ns



