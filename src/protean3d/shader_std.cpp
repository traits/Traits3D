#include "shader_std.h"

const std::string Protean3D::GL::ShaderCode::Vertex::proj_matrix =   "proj_matrix";
const std::string Protean3D::GL::ShaderCode::Vertex::mv_matrix =     "mv_matrix";
const std::string Protean3D::GL::ShaderCode::Vertex::v_in_color =    "v_in_color";
const std::string Protean3D::GL::ShaderCode::Vertex::v_coordinates = "v_coordinates";
const std::string Protean3D::GL::ShaderCode::Vertex::v_normals =     "v_normals";

// Vertex shader

const char* Protean3D::GL::ShaderCode::Vertex::Line =
{
#ifdef GL_ES_VERSION_3_0
  "#version 100\n"
#else
  "#version 150\n"
#endif
  "uniform mat4 proj_matrix; \n"
  "uniform mat4 mv_matrix; \n"
  "in vec3 v_coordinates;\n"
  "in vec3 v_normals;\n"
  "uniform vec4 v_in_color;\n"
  "out vec4 v_out_color;\n"
  "void main()\n"
  "{"
  "   gl_Position = proj_matrix * mv_matrix * vec4(v_coordinates, 1.0);\n"
  "   v_out_color = v_in_color;\n"
  "}"
};

const char* Protean3D::GL::ShaderCode::Vertex::TriangleStrip =
{
#ifdef GL_ES_VERSION_3_0
  "#version 100\n"
#else
  "#version 150\n"
#endif
  "uniform mat4 proj_matrix; \n"
  "uniform mat4 mv_matrix; \n"
  "in vec3 v_coordinates;\n"
  "in vec3 v_normals;\n"
  "in vec4 v_in_color;\n"
  "out vec4 v_out_color;\n"
  "void main()\n"
  "{"
  "   gl_Position = proj_matrix * mv_matrix * vec4(v_coordinates, 1.0);\n"
  "   v_out_color = v_in_color;\n"
  "}"
};

const char* Protean3D::GL::ShaderCode::Vertex::LineXYZ =
{
#ifdef GL_ES_VERSION_3_0
  "#version 100\n"
#else
  "#version 150\n"
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
  "}"
};

const char* Protean3D::GL::ShaderCode::Vertex::TriangleStripXYZ =
{
#ifdef GL_ES_VERSION_3_0
  "#version 100\n"
#else
  "#version 150\n"
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
  "}"
};


// Fragment Shader

const char* Protean3D::GL::ShaderCode::Fragment::Simple =
{
#ifdef GL_ES_VERSION_3_0
  "#version 100\n"
#else
  "#version 150\n"
#endif
  "in vec4 v_out_color;\n"
  "out vec4 gl_FragColor;\n"
  "void main()\n"
  "{"
  "  gl_FragColor = v_out_color;\n"
  "}"
};

