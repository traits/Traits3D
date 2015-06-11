#pragma once

// generated file - don't touch

#include <string>

namespace Traits3D
{
  namespace GL
  {
    namespace ShaderCode
    {
      // shader variables
      struct Var
      {
        static const std::string f_out_color;
        static const std::string light_position;
        static const std::string mv_matrix;
        static const std::string normal_matrix;
        static const std::string proj_matrix;
        static const std::string v_coordinates;
        static const std::string v_in_color;
        static const std::string v_normals;
        static const std::string v_out_color;
      };

      // Vertex shader
      class Vertex
      {
      public:
        static const char* BlinnPhong;
        static const char* Line;
        static const char* LineXYZ;
        static const char* Phong;
        static const char* TriangleStrip;
        static const char* TriangleStripXYZ;
      };

      // Fragment shader
      class Fragment
      {
      public:
        static const char* BlinnPhong;
        static const char* Phong;
        static const char* Simple;
      };

    } // ShaderCode
  } // GL
} // Traits3D
