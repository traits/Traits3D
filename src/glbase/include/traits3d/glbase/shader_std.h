#pragma once

// generated file - don't touch

#include <string>

namespace glb
{
  namespace shadercode
  {
    // shader variables
    struct Var
    {
      static const std::string f_out_color;
      static const std::string light_position;
      static const std::string light_position2;
      static const std::string mv_matrix;
      static const std::string normal_matrix;
      static const std::string proj_matrix;
      static const std::string v_coordinates;
      static const std::string v_in_color;
      static const std::string v_normals;
      static const std::string v_out_color;
    };

    // Fragment shader 
    class Fragment
    {
    public:
      static const char* Blinn;
      static const char* BlinnPhong;
      static const char* Simple;
    };

    // Subroutine shader 
    class Subroutine
    {
    public:
    };

    // Vertex shader 
    class Vertex
    {
    public:
      static const char* Blinn;
      static const char* BlinnPhong;
      static const char* Line;
      static const char* LineXYZ;
      static const char* TriangleStrip;
      static const char* TriangleStripXYZ;
    };

  } // shadercode
} // glb
