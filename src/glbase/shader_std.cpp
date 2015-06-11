// generated file - don't touch

#include "traits3d/glbase/shader_std.h"

const std::string Traits3D::GL::ShaderCode::Var::f_out_color = "f_out_color";
const std::string Traits3D::GL::ShaderCode::Var::light_position = "light_position";
const std::string Traits3D::GL::ShaderCode::Var::mv_matrix = "mv_matrix";
const std::string Traits3D::GL::ShaderCode::Var::normal_matrix = "normal_matrix";
const std::string Traits3D::GL::ShaderCode::Var::proj_matrix = "proj_matrix";
const std::string Traits3D::GL::ShaderCode::Var::v_coordinates = "v_coordinates";
const std::string Traits3D::GL::ShaderCode::Var::v_in_color = "v_in_color";
const std::string Traits3D::GL::ShaderCode::Var::v_normals = "v_normals";
const std::string Traits3D::GL::ShaderCode::Var::v_out_color = "v_out_color";


// Vertex shader


// BlinnPhong.tglsl
const char* Traits3D::GL::ShaderCode::Vertex::BlinnPhong = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "uniform mat4 proj_matrix;\n"
  "uniform mat4 mv_matrix;\n"
  "uniform mat3 normal_matrix;\n"
  "layout (location = 0) in vec3 v_coordinates;\n"
  "in vec3 v_normals;\n"
  "in vec4 v_in_color;\n"
  "out vec3 normal_out;\n"
  "out vec3 vert_out;\n"
  "out vec4 v_out_color;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = proj_matrix * mv_matrix * vec4(v_coordinates, 1.0);\n"
  "   v_out_color = v_in_color;\n"
  "   vec4 vertPos4 = mv_matrix * vec4(v_coordinates, 1.0);\n"
  "   vert_out = vec3(vertPos4) / vertPos4.w;\n"
  "   normal_out = normal_matrix * v_normals;\n"
  "}\n"
};



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



// Phong.tglsl
const char* Traits3D::GL::ShaderCode::Vertex::Phong = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "uniform mat4 proj_matrix;\n"
  "uniform mat4 mv_matrix;\n"
  "uniform mat3 normal_matrix;\n"
  "layout (location = 0) in vec3 v_coordinates;\n"
  "in vec3 v_normals;\n"
  "in vec4 v_in_color;\n"
  "out vec3 normal_out;\n"
  "out vec3 vert_out;\n"
  "out vec4 v_out_color;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = proj_matrix * mv_matrix * vec4(v_coordinates, 1.0);\n"
  "   v_out_color = v_in_color;\n"
  "   vec4 vertPos4 = mv_matrix * vec4(v_coordinates, 1.0);\n"
  "   vert_out = vec3(vertPos4) / vertPos4.w;\n"
  "   normal_out = normal_matrix * v_normals;\n"
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


// BlinnPhong.tglsl
const char* Traits3D::GL::ShaderCode::Fragment::BlinnPhong = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "in vec3 normal_out;\n"
  "in vec3 vert_out;\n"
  "in vec4 v_out_color;\n"
  "out vec4 f_out_color;\n"
  "//uniform int mode;\n"
  "const vec3 lightPos = vec3(1.0,1.0,-15.0);\n"
  "const vec3 ambientColor = vec3(0.2, 0.0, 0.0);\n"
  "//const vec3 diffuseColor = vec3(0.5, 0.0, 0.0);\n"
  "vec3 diffuseColor = vec3(v_out_color);\n"
  "const vec3 specColor = vec3(1.0, 1.0, 1.0);\n"
  "void main() \n"
  "{\n"
  "  vec3 normal = normalize(normal_out);\n"
  "  vec3 lightDir = normalize(lightPos - vert_out);\n"
  "  float lambertian = max(dot(lightDir,normal), 0.0);\n"
  "  float specular = 0.0;\n"
  "  if(lambertian > 0.0) \n"
  "  {\n"
  "    vec3 viewDir = normalize(-vert_out);\n"
  "    // this is blinn phong\n"
  "    vec3 halfDir = normalize(lightDir + viewDir);\n"
  "    float specAngle = max(dot(halfDir, normal), 0.0);\n"
  "    specular = pow(specAngle, 16.0);\n"
  "  }\n"
  "  f_out_color = vec4(ambientColor +\n"
  "                    lambertian*diffuseColor +\n"
  "                    specular*specColor, 1.0);\n"
  "  // only ambient\n"
  "  //if(mode == 2) f_out_color = vec4(ambientColor, 1.0);\n"
  "  // only diffuse\n"
  "  //if(mode == 3) \n"
  "  //f_out_color = vec4(lambertian*diffuseColor, 1.0);\n"
  "  // only specular\n"
  "  //if(mode == 4) f_out_color = vec4(specular*specColor, 1.0);\n"
  "}\n"
};



// Phong.tglsl
const char* Traits3D::GL::ShaderCode::Fragment::Phong = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "in vec3 normal_out;\n"
  "in vec3 vert_out;\n"
  "in vec4 v_out_color;\n"
  "out vec4 f_out_color;\n"
  "//uniform int mode;\n"
  "const vec3 lightPos = vec3(1.0,1.0,3.0);\n"
  "const vec3 ambientColor = vec3(0.2, 0.0, 0.0);\n"
  "//const vec3 diffuseColor = vec3(0.5, 0.0, 0.0);\n"
  "vec3 diffuseColor = vec3(v_out_color);\n"
  "const vec3 specColor = vec3(1.0, 1.0, 1.0);\n"
  "void main() \n"
  "{\n"
  "  vec3 normal = normalize(normal_out);\n"
  "  vec3 lightDir = normalize(lightPos - vert_out);\n"
  "  vec3 reflectDir = reflect(-lightDir, normal);\n"
  "  vec3 viewDir = normalize(-vert_out);\n"
  "  float lambertian = max(dot(lightDir,normal), 0.0);\n"
  "  float specular = 0.0;\n"
  "  if(lambertian > 0.0) \n"
  "  {\n"
  "     float specAngle = max(dot(reflectDir, viewDir), 0.0);\n"
  "     specular = pow(specAngle, 4.0);\n"
  "  }\n"
  "  f_out_color = vec4(ambientColor +\n"
  "                    lambertian*diffuseColor +\n"
  "                    specular*specColor, 1.0);\n"
  "  // only ambient\n"
  "  //if(mode == 2) f_out_color = vec4(ambientColor, 1.0);\n"
  "  // only diffuse\n"
  "  //if(mode == 3) \n"
  "  //f_out_color = vec4(lambertian*diffuseColor, 1.0);\n"
  "  // only specular\n"
  "  //if(mode == 4) f_out_color = vec4(specular*specColor, 1.0);\n"
  "}\n"
};



// Simple.tglsl
const char* Traits3D::GL::ShaderCode::Fragment::Simple = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "in vec4 v_out_color;\n"
  "out vec4 f_out_color;\n"
  "void main()\n"
  "{\n"
  "  f_out_color = v_out_color;\n"
  "}\n"
};

