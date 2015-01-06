#include <vector>
#include <fstream>
#include <string>
#include "vbo.h"
#include "shader.h"

Protean3D::GL::Shader::Shader()
  : initialized_(false), program_id_(0)
{
}

bool Protean3D::GL::Shader::load(std::string& result, std::string const& path)
{
  result.clear();
  std::ifstream shader_stream(path, std::ios::in);
  if(shader_stream.is_open())
  {
    std::string Line = "";
    while(std::getline(shader_stream, Line))
      result += "\n" + Line;
    shader_stream.close();
    return true;
  }
  return false;
}

bool Protean3D::GL::Shader::compile(GLuint shader_id, std::string const& shader_code)
{
  GLint result = GL_FALSE;

  // Compile shader
  char const* text = shader_code.c_str();
  glShaderSource(shader_id, 1, &text , NULL);
  glCompileShader(shader_id);

  // Check shader
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
  if (GL_FALSE == result)
  {
    int infolog_size;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &infolog_size);
    if (infolog_size > 0){
      std::vector<char> shader_error(infolog_size + 1);
      glGetShaderInfoLog(shader_id, infolog_size, NULL, &shader_error[0]);
      printf(__FUNCTION__ ":\n%s\n", &shader_error[0]);
    }
  }
  return (GL_TRUE == result) ? true : false;
}

bool Protean3D::GL::Shader::link(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
  GLint result = GL_FALSE;

  // Link the program
  //printf("Linking program\n");
  program_id_ = glCreateProgram();
  glAttachShader(program_id_, vertex_shader_id);
  glAttachShader(program_id_, fragment_shader_id);
  glLinkProgram(program_id_);
  glDetachShader(program_id_, vertex_shader_id);
  glDetachShader(program_id_, fragment_shader_id);

  // Check the program
  glGetProgramiv(program_id_, GL_LINK_STATUS, &result);
  if (GL_FALSE == result)
  {
    int infolog_size;
    glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &infolog_size);
    if (infolog_size > 0){
      std::vector<char> program_error(infolog_size + 1);
      glGetProgramInfoLog(program_id_, infolog_size, NULL, &program_error[0]);
      printf("%s\n", &program_error[0]);
    }
  }
  return (result == GL_TRUE) ? true : false;
}

bool Protean3D::GL::Shader::create(std::string const& vertex_code, std::string const& fragment_code)
{
  initialized_ = false;

  GLuint vid = glCreateShader(GL_VERTEX_SHADER);
  GLuint fid = glCreateShader(GL_FRAGMENT_SHADER);

  if (!compile(vid, vertex_code)
    || !compile(fid, fragment_code)
    || !link(vid, fid)
    )
  {
    glDeleteShader(vid);
    glDeleteShader(fid);
    return false;
  }

  glDeleteShader(vid);
  glDeleteShader(fid);

  initialized_ = true;
  return true;
}

//bool Protean3D::GL::Shader::create()
//{
//  const char* vsrc =
//    "attribute highp vec4 vertex;\n"
//    "attribute mediump vec4 texCoord;\n"
//    "varying mediump vec4 texc;\n"
//    "uniform mediump mat4 matrix;\n"
//    "void main(void)\n"
//    "{\n"
//    "    gl_Position = matrix * vertex;\n"
//    "    texc = texCoord;\n"
//    "}\n";
//
//  const char* fsrc =
//    "uniform sampler2D texture;\n"
//    "varying mediump vec4 texc;\n"
//    "void main(void)\n"
//    "{\n"
//    "    gl_FragColor = texture2D(texture, texc.st);\n"
//    "}\n";
//
//  return  create(vsrc, fsrc);
//}

bool Protean3D::GL::Shader::createFromFile(std::string const& vertex_file_path, std::string const& fragment_file_path)
{
  std::string vertex_code;
  if (!load(vertex_code, vertex_file_path))
    return false;

  std::string fragment_code;
  if (!load(fragment_code, fragment_file_path))
    return false;

  return create(vertex_code, fragment_code);
}

bool Protean3D::GL::Shader::setUniformMatrix(glm::mat4 const& mat, std::string const& name)
{
  if (name.empty() || !use())
    return false;

  GLint loc = glGetUniformLocation(program_id_, name.c_str());
  if (-1 == loc || GL_NO_ERROR != glGetError())
    return false;

  glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
  if (GL_NO_ERROR != glGetError())
    return false;

  return true;
}

bool Protean3D::GL::Shader::setUniformVec4(glm::vec4 const& vec, std::string const& name)
{
  if (name.empty() || !use())
    return false;

  GLint loc = glGetUniformLocation(program_id_, name.c_str());
  if (-1 == loc || GL_NO_ERROR != glGetError())
    return false;

  glUniform4fv(loc, 1, &vec[0]);
  if (GL_NO_ERROR != glGetError())
    return false;

  return true;
}

bool Protean3D::GL::Shader::setProjectionMatrix(glm::mat4 const& mat)
{
  return setUniformMatrix(mat, ShaderCode::Vertex::proj_matrix);
}


bool Protean3D::GL::Shader::setModelViewMatrix(glm::mat4 const& mat)
{
  return setUniformMatrix(mat, ShaderCode::Vertex::mv_matrix);
}

bool Protean3D::GL::Shader::use()
{
  if (!initialized_)
    return false;

  if (inUse())
    return true;

  glUseProgram(program_id_);
  if (GL_NO_ERROR != glGetError())
    return false;

  return true;
}

bool Protean3D::GL::Shader::inUse() const
{
  if (!initialized_)
    return false;

  GLint currprog;
  glGetIntegerv(GL_CURRENT_PROGRAM, &currprog);
  if (GL_NO_ERROR != glGetError())
    return false;

  return static_cast<GLuint>(currprog) == program_id_;
}

bool Protean3D::GL::Shader::bindAttribute(VBO& vbo, std::string const& name)
{
  if (name.empty())
    return false;

  GLuint attrloc = glGetAttribLocation(program_id_, name.c_str());
  if (GL_NO_ERROR != glGetError())
    return false;

  return vbo.bindAttribute(attrloc);
}
