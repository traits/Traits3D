// generated file - don't touch

#include "traits3d/glbase/shader_std.h"

const std::string Traits3D::GL::ShaderCode::Var::mv_matrix = "mv_matrix";
const std::string Traits3D::GL::ShaderCode::Var::proj_matrix = "proj_matrix";
const std::string Traits3D::GL::ShaderCode::Var::v_coordinates = "v_coordinates";
const std::string Traits3D::GL::ShaderCode::Var::v_in_color = "v_in_color";
const std::string Traits3D::GL::ShaderCode::Var::v_normals = "v_normals";
const std::string Traits3D::GL::ShaderCode::Var::v_out_color = "v_out_color";


// Vertex shader


// Line.tgsl
const char* Traits3D::GL::ShaderCode::Vertex::Line = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "uniform mat4 proj_matrix;\n"
  "uniform mat4 mv_matrix;\n"
  "layout (location = 0) in vec3 v_coordinates;\n"
  "in vec3 v_normals;\n"
  "uniform vec4 v_in_color;\n"
  "out vec4 v_out_color;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = proj_matrix * mv_matrix * vec4(v_coordinates, 1.0);\n"
  "   v_out_color = v_in_color;\n"
  "}\n"
};



// LineXYZ.tgsl
const char* Traits3D::GL::ShaderCode::Vertex::LineXYZ = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "uniform mat4 proj_matrix;\n"
  "uniform mat4 mv_matrix;\n"
  "in float x;\n"
  "in float y;\n"
  "in float z;\n"
  "uniform vec4 v_in_color;\n"
  "out vec4 v_out_color;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = proj_matrix * mv_matrix * vec4(x, y, z, 1.0);\n"
  "   v_out_color = v_in_color;\n"
  "}\n"
};



// TriangleStrip.tgsl
const char* Traits3D::GL::ShaderCode::Vertex::TriangleStrip = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "uniform mat4 proj_matrix;\n"
  "uniform mat4 mv_matrix;\n"
  "layout (location = 0) in vec3 v_coordinates;\n"
  "in vec3 v_normals;\n"
  "in vec4 v_in_color;\n"
  "out vec4 v_out_color;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = proj_matrix * mv_matrix * vec4(v_coordinates, 1.0);\n"
  "   v_out_color = v_in_color;\n"
  "}\n"
};



// TriangleStripXYZ.tgsl
const char* Traits3D::GL::ShaderCode::Vertex::TriangleStripXYZ = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "uniform mat4 proj_matrix;\n"
  "uniform mat4 mv_matrix;\n"
  "in float x;\n"
  "in float y;\n"
  "in float z;\n"
  "in vec4 v_in_color;\n"
  "out vec4 v_out_color;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = proj_matrix * mv_matrix * vec4(x, y, z, 1.0);\n"
  "   v_out_color = v_in_color;\n"
  "}\n"
};



// Fragment shader


// Simple.glsl
const char* Traits3D::GL::ShaderCode::Fragment::Simple = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "in vec4 v_out_color;\n"
  "out vec4 frag_color;\n"
  "void main()\n"
  "{\n"
  "  frag_color = v_out_color;\n"
  "}\n"
};

