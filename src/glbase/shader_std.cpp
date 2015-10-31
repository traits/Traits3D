// generated file - don't touch

#include "traits3d/glbase/shader_std.h"

namespace Traits3D
{
namespace GL
{
namespace ShaderCode
{

const std::string Var::f_out_color = "f_out_color";
const std::string Var::light_position = "light_position";
const std::string Var::light_position2 = "light_position2";
const std::string Var::mv_matrix = "mv_matrix";
const std::string Var::normal_matrix = "normal_matrix";
const std::string Var::proj_matrix = "proj_matrix";
const std::string Var::v_coordinates = "v_coordinates";
const std::string Var::v_in_color = "v_in_color";
const std::string Var::v_normals = "v_normals";
const std::string Var::v_out_color = "v_out_color";


// Fragment shader


// Blinn.fsht
const char* Fragment::Blinn = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "in vec4 v_out_color;\n"
  "in vec3 N;\n"
  "in vec3 V;\n"
  "in vec3 L;\n"
  "out vec4 f_out_color;\n"
  "const vec3 AmbientColour = vec3(0.2, 0.0, 0.0);\n"
  "vec3 DiffuseColour = vec3(v_out_color);\n"
  "const vec3 SpecularColour = vec3(1.0, 1.0, 1.0);\n"
  "const float AmbientIntensity = 1.0;\n"
  "const float DiffuseIntensity = 1.0;\n"
  "const float SpecularIntensity = 1.0;\n"
  "const float Roughness = 1.0/16.0;\n"
  "float strictSign(float x)\n"
  "{\n"
  "	return step(0, x)*2 - 1;\n"
  "}\n"
  "void main()\n"
  "{ \n"
  "    vec3 l = normalize(L);\n"
  "    vec3 n = normalize(N);\n"
  "    vec3 v = normalize(-V);\n"
  "    vec3 h = normalize(l+v);\n"
  "    float diffuse = dot(l,n);\n"
  "    float s = strictSign(diffuse);\n"
  "    diffuse = s * diffuse;\n"
  "    n = s * n;\n"
  "    float specular = pow(max(0.0,dot(n,h)),1/Roughness);\n"
  "    f_out_color = vec4(AmbientColour*AmbientIntensity + \n"
  "                        DiffuseColour*diffuse*DiffuseIntensity +\n"
  "                        SpecularColour*specular*SpecularIntensity,1);\n"
  "}\n"
};



// BlinnPhong.fsht
const char* Fragment::BlinnPhong = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "in vec3 normal_out;\n"
  "in vec3 vert_out;\n"
  "in vec4 v_out_color;\n"
  "in vec3 light_position;\n"
  "in vec3 light_position2;\n"
  "out vec4 f_out_color;\n"
  "vec3 diffuseColor = vec3(v_out_color);\n"
  "const vec3 ambientColor = vec3(0.2, 0.0, 0.0);\n"
  "const vec3 specColor = vec3(1.0, 1.0, 1.0);\n"
  "float strictSign(float x)\n"
  "{\n"
  "	return step(0, x)*2 - 1;\n"
  "}\n"
  "void main() \n"
  "{\n"
  "  vec3 normal = normalize(normal_out);\n"
  "  vec3 lightDir = -normalize(light_position2 - vert_out);\n"
  "  float lambertian = dot(lightDir,normal);\n"
  "  float s = strictSign(lambertian);\n"
  "  lambertian = s * lambertian;\n"
  "  normal = s * normal;\n"
  "  float specular = 0.0;\n"
  "  vec3 viewDir = normalize(-vert_out);\n"
  "  vec3 halfDir = normalize(lightDir + viewDir);\n"
  "  float specAngle = max(dot(halfDir, normal), 0.0);\n"
  "  specular = pow(specAngle, 16.0);\n"
  "  f_out_color = vec4(ambientColor +\n"
  "                    lambertian*diffuseColor +\n"
  "                    specular*specColor, 1.0);\n"
  "}\n"
};



// Simple.fsht
const char* Fragment::Simple = 
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



// Subroutine shader


// Vertex shader


// Blinn.vsht
const char* Vertex::Blinn = 
{
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\n"
#else
  "#version 330\n"
#endif
  "uniform mat4 proj_matrix;\n"
  "uniform mat4 mv_matrix;\n"
  "uniform mat3 normal_matrix;\n"
  "uniform vec3 light_position;\n"
  "layout (location = 0) in vec3 v_coordinates;\n"
  "in vec3 v_normals;\n"
  "in vec4 v_in_color;\n"
  "out vec4 v_out_color;\n"
  "out vec3 N;\n"
  "out vec3 V;\n"
  "out vec3 L;\n"
  "void main()\n"
  "{    \n"
  "    N = normalize(normal_matrix*v_normals);\n"
  "    V = vec3(mv_matrix * vec4(v_coordinates, 1.0));\n"
  "	  L = light_position - V;\n"
  "    v_out_color = v_in_color;\n"
  "    gl_Position = proj_matrix * mv_matrix * vec4(v_coordinates, 1.0);\n"
  "}\n"
};



// BlinnPhong.vsht
const char* Vertex::BlinnPhong = 
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
  "in vec3 light_position;\n"
  "out vec3 light_position2;\n"
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
  "   light_position2 = vec3(mv_matrix * vec4(light_position, 1.0));\n"
  "}\n"
};



// Line.vsht
const char* Vertex::Line = 
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



// LineXYZ.vsht
const char* Vertex::LineXYZ = 
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



// TriangleStrip.vsht
const char* Vertex::TriangleStrip = 
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



// TriangleStripXYZ.vsht
const char* Vertex::TriangleStripXYZ = 
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

} // ShaderCode
} // GL
} // Traits3D
