#pragma once

#include <string>

namespace Traits3D
{
  namespace GL
  {
    namespace ShaderCode
    {
      class Vertex
      {
      public:
        // variable access
        static const std::string proj_matrix;
        static const std::string mv_matrix;
        static const std::string v_in_color;
        static const std::string v_coordinates;
        static const std::string v_normals;

        // shaders
        static const char* Line;
        static const char* TriangleStrip;
        static const char* LineXYZ;
        static const char* TriangleStripXYZ;
      };

      class Fragment
      {
      public:
        static const char* Simple;
      };

    }
  }
}